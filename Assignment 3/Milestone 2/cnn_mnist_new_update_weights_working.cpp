#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include<immintrin.h>

using namespace std;
const int filter_size=7;
const double eta[]={0.01,0.01,0.01,0.01};
const int batch_size=200;

int data_train[60000][784];
int data_test[10000][784];
int label_train[60000];
int label_test[10000];

double conv_w[5][7][7];
double conv_b[5][28][28];
double conv_layer[5][28][28];
double sig_layer[5][28][28];
char max_pooling[5][28][28];
double max_layer[5][14][14];

double dense_input[980];
double dense_w[980][120];
double dense_b[120];
double dense_sum[120];
double dense_sigmoid[120];
double dense_w2[120][10];
double dense_b2[10];
double dense_sum2[10];
double dense_softmax[10];

double dw2[120][10];
double db2[10];
double dw1[980][120];
double db1[120];

double dw_max[5][28][28];
double dw_conv[5][7][7];
double db_conv[5][28][28];


/* ************************************************************ */
/* Helper functions */
double sigmoid(double x) {
	if (x>500) x=500;
	if (x<-500) x=-500;
	return 1/(1+exp(-x));
}
double d_sigmoid(double x) {
	double sig = sigmoid(x);
	return sig*(1-sig);
}
double softmax_den(double *x, int len) {
	double val =0;
	for (int i=0; i<len; i++) {
		val += exp(x[i]);
	}
	return val;
}

void initialise_weights() {
	for (int i=0; i<5; i++) {
		for (int j=0; j<28; j++) {
			for (int k=0; k<28; k++) {
				if (j<7 && k<7) {
					conv_w[i][j][k] = 2*double(rand())/RAND_MAX-1;
				}
				conv_b[i][j][k] = 2*double(rand())/RAND_MAX-1;
			}
		}
	}

	for (int i=0; i<980; i++) {
		for (int j=0; j<120; j++) {
			dense_w[i][j] = 2*double(rand()) / RAND_MAX-1;
		}
	}
	for (int i=0; i<120; i++) {
		dense_b[i] = 2*double(rand()) / RAND_MAX-1;
	}

	for (int i=0; i<120; i++) {
		for (int j=0; j<10; j++) {
			dense_w2[i][j] = 2*double(rand())/RAND_MAX-1;
		}
	}
	for (int i=0; i<10; i++) {
		dense_b2[i] = 2*double(rand())/RAND_MAX-1;
	}
}
/* ************************************************************ */

/* ************************************************************ */
/* Forward Pass */
void forward_pass(int img[][32]) {

	// Convolution Operation + Sigmoid Activation
	for (int filter_dim=0; filter_dim<5; filter_dim++) {
		for (int i=0; i<28; i++) {
			for (int j=0; j<28; j++) {
				max_pooling[filter_dim][i][j] = 0;

				conv_layer[filter_dim][i][j] = 0;
				sig_layer[filter_dim][i][j] = 0;
				for (int k=0; k<filter_size; k++) {
					for (int l=0; l<filter_size; l++) {
						conv_layer[filter_dim][i][j] = img[-2+i+k][-2+j+l]*conv_w[filter_dim][k][l];
					}
				}
				sig_layer[filter_dim][i][j] = sigmoid(conv_layer[filter_dim][i][j] + conv_b[filter_dim][i][j]);
			}
		}
	}

	// MAX Pooling (max_pooling, max_layer)
	double cur_max =0;
	int max_i=0, max_j=0;
	for (int filter_dim=0; filter_dim<5; filter_dim++) {
		for (int i=0; i<28; i+=2) {
			for (int j=0; j<28; j+=2) {
				max_i=i;
				max_j=j;
				cur_max=sig_layer[filter_dim][i][j];
				for (int k=0; k<2; k++) {
					for (int l=0; l<2; l++) {
						if (sig_layer[filter_dim][i+k][j+l] > cur_max) {
							max_i = i+k;
							max_j = j+l;
							cur_max = sig_layer[filter_dim][max_i][max_j];
						}
					}
				}
				max_pooling[filter_dim][max_i][max_j] = 1;
				max_layer[filter_dim][i/2][j/2] = cur_max;
			}
		}
	}

	int k=0;
	for (int filter_dim=0;filter_dim<5;filter_dim++) {
		for (int i=0;i<14;i++) {
			for (int j=0;j<14;j++) {
				dense_input[k] = max_layer[filter_dim][i][j];
				k++;
			}
		}
	}

	// Dense Layer
	for (int i=0; i<120; i++) {
		dense_sum[i] = 0;
		dense_sigmoid[i] = 0;
		for (int j=0; j<980; j++) {
			dense_sum[i] += dense_w[j][i] * dense_input[j];
		}
		dense_sum[i] += dense_b[i];
		dense_sigmoid[i] = sigmoid(dense_sum[i]);
	}

	// Dense Layer 2
	for (int i=0; i<10; i++) {
		dense_sum2[i]=0;
		for (int j=0; j<120; j++) {
			dense_sum2[i] += dense_w2[j][i] * dense_sigmoid[j];
		}
		dense_sum2[i] += dense_b2[i];
	}

	// Softmax Output
	double den = softmax_den(dense_sum2, 10);
	for (int i=0; i<10; i++) {
		dense_softmax[i] = exp(dense_sum2[i])/den;
	}
}

void update_weights() {
  __m256d dense_local1,dense_local2,dense_local3,dense_local4,dense_local5,dense_local6,dense_local7;
	for (int i=0; i<120; i++) {
		dense_b[i] -= eta[1]*db1[i];
    int j,k;
		for (j=0; j<7; j+=4) {
      //cout<<"testing1"<<i<<j<<endl;
      dense_local1 = _mm256_loadu_pd(&db2[j]);
      //cout<<"testing2"<<j<<endl;
      dense_local2 = _mm256_loadu_pd(&dw2[i][j]);
      //cout<<"testing3"<<j<<endl;
      dense_local7 = _mm256_loadu_pd(&eta[0]);
      //cout<<"testing4"<<j<<endl;
      dense_local3 = _mm256_mul_pd(dense_local7,dense_local1);
      //cout<<"testing5"<<j<<endl;
      dense_local4 = _mm256_mul_pd(dense_local7,dense_local2);
      //cout<<"testing6"<<j<<endl;
      dense_local5 = _mm256_sub_pd (_mm256_loadu_pd(&dense_b2[j]),dense_local3);
      //cout<<"testing7"<<j<<endl;
      dense_local6 = _mm256_sub_pd (_mm256_loadu_pd(&dense_w2[i][j]),dense_local4);
      //cout<<"testing8"<<j<<endl;
      _mm256_storeu_pd(&dense_b2[j],dense_local5);
      //cout<<"testing9"<<j<<endl;
      _mm256_storeu_pd(&dense_w2[i][j],dense_local6);
      //cout<<"testing10"<<j<<endl;
			//dense_b2[j] -= eta*db2[j];
			//dense_w2[i][j] -= eta*dw2[i][j];
		}
    for(j=8;j<10;j++){
    dense_b2[j] -= eta[1]*db2[j];
		dense_w2[i][j] -= eta[1]*dw2[i][j];
    }
    //cout<<"testing11"<<j<<i<<endl;
		for (k=0; k<980; k+=4) {
      dense_local1 = _mm256_loadu_pd(&dw1[k][i]);
      dense_local7 = _mm256_loadu_pd(&eta[0]);
      dense_local3 = _mm256_mul_pd(dense_local7,dense_local1);
      dense_local5 = _mm256_sub_pd (_mm256_loadu_pd(&dense_w[k][i]),dense_local3);
      _mm256_storeu_pd(&dense_w[k][i],dense_local5);
			//dense_w[k][i] -= eta[1]*dw1[k][i];
		}
	}

	for (int i=0; i<5; i++) {
		for (int k=0; k<7; k++) {
			for (int j=0; j<7; j++) {
				conv_w[i][k][j] -= eta[1]*dw_conv[i][k][j];
			}
		}
		for (int l=0; l<28; l++) {
			for (int m=0; m<28; m+=4) {
        dense_local1 = _mm256_loadu_pd(&db_conv[i][l][m]);
        dense_local7 = _mm256_loadu_pd(&eta[0]);
        dense_local3 = _mm256_mul_pd(dense_local7,dense_local1);
        dense_local5 = _mm256_sub_pd (_mm256_loadu_pd(&conv_b[i][l][m]),dense_local3);
        _mm256_storeu_pd(&conv_b[i][l][m],dense_local5);
				//conv_b[i][l][m] -= eta[1]*db_conv[i][l][m];
			}
		}
	}
}
/* ************************************************************ */

/* ************************************************************ */
/* Backward Pass */
void backward_pass(double *y_hat, int *y, int img[][32]) {
	__m256d bpass1,bpass2,bpass3,bpass4;
  double delta4[10];
	for (int i=0; i<10; i++) {
		delta4[i] = y_hat[i] - y[i]; // Derivative of Softmax + Cross entropy
		db2[i] = delta4[i]; // Bias Changes
	}

	// Calculate Weight Changes for Dense Layer 2
	for (int i=0; i<120; i++) {
		for (int j=0; j<7; j+=4) {
      bpass1 = _mm256_loadu_pd(&delta4[j]);
      bpass2 = _mm256_loadu_pd(&dense_sigmoid[i]);
      bpass3 = _mm256_mul_pd(bpass1,bpass2);
      _mm256_storeu_pd(&dw2[i][j],bpass3);
			//dw2[i][j] = dense_sigmoid[i]*delta4[j];
		}
   for(int j=8; j<10; j++){
     dw2[i][j] = dense_sigmoid[i]*delta4[j];
   }
	}

	// Delta 3
	double delta3[120];
	for (int i=0; i<120; i++) {
		delta3[i] = 0;
		for (int j=0; j<10; j++) {
      bpass1 = _mm256_loadu_pd(&delta4[j]);
      bpass2 = _mm256_loadu_pd(&dense_w2[i][j]);
      bpass3 = _mm256_mul_pd(bpass1,bpass2);
      bpass4 = _mm256_add_pd(_mm256_loadu_pd(&delta3[i]),bpass3);
      _mm256_storeu_pd(&dw2[i][j],bpass4);
			//delta3[i] += dense_w2[i][j]*delta4[j];
		}
		delta3[i] *= d_sigmoid(dense_sum[i]);
	}
	for (int i=0; i<120; i++) db1[i] = delta3[i]; // Bias Weight change

	// Calculate Weight Changes for Dense Layer 1
	for (int i=0; i<980; i++) {
		for (int j=0; j<120; j++) {
			dw1[i][j] = dense_input[i]*delta3[j];
		}
	}

	// Delta2
	double delta2[980];
	for (int i=0; i<980; i++) {
		delta2[i] = 0;
		for (int j=0; j<120; j++) {
			delta2[i] += dense_w[i][j]*delta3[j];
		}
		delta2[i] *= d_sigmoid(dense_input[i]);
	}

	// Calc back-propagated max layer dw_max
	int k=0;
	for (int filter_dim=0; filter_dim<5; filter_dim++) {
		for (int i=0; i<28; i+= 2) {
			for (int j=0; j<28; j+= 2) {
				for (int l=0; l<2; l++) {
					for (int m=0; m<2; m++) {
						if (max_pooling[filter_dim][i+l][j+m] == 1) dw_max[filter_dim][i][j] = delta2[k];
						else dw_max[filter_dim][i][j] = 0;
					}
				}
				k++;
			}
		}
	}
	// Calc Conv Bias Changes
	for (int filter_dim=0; filter_dim<5; filter_dim++) {
		for (int i=0; i<28; i++) {
			for (int j=0; j<28; j++) {
				db_conv[filter_dim][i][j] = dw_max[filter_dim][i][j];
			}
		}
	}

	// Set Conv Layer Weight changes to 0
	for (int filter_dim=0; filter_dim<5; filter_dim++) {
		for (int i=0; i<5; i++) {
			for (int j=0; j<5; j++) {
				dw_conv[filter_dim][i][j] = 0;
			}
		}
	}

	// Calculate Weight Changes for Conv Layer
	for (int filter_dim=0; filter_dim<5; filter_dim++) {
		for (int i=0; i<28; i++) {
			for (int j=0; j<28; j++) {
				double cur_val = dw_max[filter_dim][i][j];
				for (int k=0; k<5; k++) {
					for (int l=0; l<5; l++) {
						dw_conv[filter_dim][k][l] += img[i-2+k][j-2+l] * cur_val;
					}
				}
			}
		}
	}


}
/* ************************************************************ */


void read_train_data() {
	ifstream csvread;
	csvread.open("/cad2/ece1718s/mnist_train.csv", ios::in);
	if(csvread) {
		string s;
		int data_pt = 0;
		while(getline(csvread, s)) {
			stringstream ss(s);
			int pxl = 0;
			while( ss.good() ) {
				string substr;
				getline(ss, substr,',');
				if (pxl == 0) {
					label_train[data_pt] = stoi(substr);
				} else {
					data_train[data_pt][pxl-1] = stoi(substr);
				}
				pxl++;
			}
			data_pt++;
		}
		csvread.close();
	}
	else{
		cerr << "Unable to read train data!" << endl;
        exit (EXIT_FAILURE);
	}
}
void read_test_data() {
	ifstream csvread;
	csvread.open("/cad2/ece1718s/mnist_test.csv", ios::in);
	if(csvread) {
		string s;
		int data_pt = 0;
		while(getline(csvread, s)) {
			stringstream ss(s);
			int pxl = 0;
			while( ss.good() ) {
				string substr;
				getline(ss, substr,',');
				if (pxl == 0) {
					label_test[data_pt] = stoi(substr);
				} else {
					data_test[data_pt][pxl-1] = stoi(substr);
				}
				pxl++;
			}
			data_pt++;
		}
		csvread.close();
	}
	else{
		cerr << "Unable to read test data!" << endl;
        exit (EXIT_FAILURE);
	}
}

void give_img(int* vec , int img[][32]) {
	int k=0;
	for (int i=0; i<32; i++) {
		for (int j=0; j<32; j++) {
			if (i<2 || j<2) {
				img[i][j] = 0;
			} else {
				img[i][j] = vec[k];
				k++;
			}
		}
	}
}

void give_y(int y, int *vector_y) {
	for (int i=0; i<10; i++) vector_y[i] =0;
	vector_y[y]=1;
}
int give_prediction() {
	double max_val = dense_softmax[0];
	int max_pos = 0;
	for (int i=1; i<10; i++) {
		if (dense_softmax[i] > max_val) {
			max_val = dense_softmax[i];
			max_pos = i;
		}
	}

	return max_pos;
}

int main() {
	read_test_data();
	read_train_data();
	initialise_weights();

	int epoch = 500;
	int num = 0;
	cout << "Start Training." << endl;
	for (int i=0; i<epoch; i++) {
		cout << "Epoch " << i << " done." << endl;
		for (int j=0; j<batch_size; j++) {
			num = rand()%60000;
			int img[32][32];
			int vector_y[10];
			give_y(label_train[num], vector_y);
			give_img(data_train[num], img);
			forward_pass(img);
			backward_pass(dense_softmax, vector_y, img);
			update_weights();
		}
	}

	int val_len = 600;
	int cor=0;
	int confusion_mat[10][10];
	for (int i=0; i<10; i++){
		for (int j=0; j<10; j++) confusion_mat[i][j] = 0;
	}

	cout << "Start Testing." << endl;
	for (int i=0; i<val_len; i++) {
		int img[32][32];
		give_img(data_test[i], img);
		forward_pass(img);
		int pre = give_prediction();
		confusion_mat[label_test[i]][pre]++;
		if (pre == label_test[i]) cor++;
	}
	float accu = double(cor)/val_len;
	cout << "Accuracy: " << accu << endl;

	cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
	for (int i=0; i<10; i++){
		cout << i << ": ";
		for (int j=0; j<10; j++) {
			cout << confusion_mat[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
