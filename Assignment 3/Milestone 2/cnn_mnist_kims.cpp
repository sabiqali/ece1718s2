#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

#include <immintrin.h>
#include <avx2intrin.h>

using namespace std;
const int filter_size = 7;
const double eta = 0.01;
const int batch_size = 200;

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

//temporary struct for checking total data footprint
/* struct data_footprint {
    const int filter_size = 7;
    const double eta = 0.01;
    const int batch_size = 200;

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
}; */

/* ************************************************************ */
/* Helper functions */
double sigmoid(double x) {
    if (x > 500) x = 500;
    if (x < -500) x = -500;
    return 1 / (1 + exp(-x));
}
double d_sigmoid(double x) {
    double sig = sigmoid(x);
    return sig * (1 - sig);
}
double softmax_den(double *x, int len) {
    double val = 0;
    for (int i = 0; i < len; i++) {
        val += exp(x[i]);
    }
    return val;
}

void initialise_weights() {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 28; j++) {
            for (int k = 0; k < 28; k++) {
                if (j < 7 && k < 7) {
                    conv_w[i][j][k] = 2 * double(rand()) / RAND_MAX - 1;
                }
                conv_b[i][j][k] = 2 * double(rand()) / RAND_MAX - 1;
            }
        }
    }

    for (int i = 0; i < 980; i++) {
        for (int j = 0; j < 120; j++) {
            dense_w[i][j] = 2 * double(rand()) / RAND_MAX - 1;
        }
    }
    for (int i = 0; i < 120; i++) {
        dense_b[i] = 2 * double(rand()) / RAND_MAX - 1;
    }

    for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 10; j++) {
            dense_w2[i][j] = 2 * double(rand()) / RAND_MAX - 1;
        }
    }
    for (int i = 0; i < 10; i++) {
        dense_b2[i] = 2 * double(rand()) / RAND_MAX - 1;
    }
}
/* ************************************************************ */

/* ************************************************************ */
/* Forward Pass */
void forward_pass(int img[][32]) {
    // Convolution Operation + Sigmoid Activation
    //** Inializing 
    int img_size = sizeof(img)/sizeof(img[0][0]);
    double double_img[32][32];
    for(int i = 0, i < 32; i++){
        for(int j = 0, j < 32; j++){
            double_img[i][j] = img[i][j];
        }
    }
    //** Set value, can't speed up
    for (int filter_dim = 0; filter_dim < 5; filter_dim++){
        for (int i = 0; i < 28; i++)Z{
            for (int j = 0; j < 28; j++){
                max_pooling[filter_dim][i][j] = 0;
                conv_layer[filter_dim][i][j] = 0;
                sig_layer[filter_dim][i][j] = 0;
            }
        }
    }
    /////////////////Not done///////////////////
    __m256d a_local, b_local, result_local, mid_local;
    double *a_start = NULL;
    double *b_start = NULL;
    double *c_strat = NULL;

    // Memory is not continus
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                for (int k = 0; k < filter_size; k++) {
                    for (int l = 0; l < filter_size; l++) {
                        conv_layer[filter_dim][i][j] = img[-2 + i + k][-2 + j + l] * conv_w[filter_dim][k][l];
                    }
                }
            }
        }
    }
    /////////////////Not done///////////////////
    // We have sigmoid here, not sure whether can we speed up
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                sig_layer[filter_dim][i][j] = sigmoid(conv_layer[filter_dim][i][j] + conv_b[filter_dim][i][j]);
            }
        }
    }

    //** MAX Pooling (max_pooling, max_layer) don't need speed up
    double cur_max = 0;
    int max_i = 0, max_j = 0;
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 28; i += 2) {
            for (int j = 0; j < 28; j += 2) {
                max_i = i;
                max_j = j;
                cur_max = sig_layer[filter_dim][i][j];
                for (int k = 0; k < 2; k++) {
                    for (int l = 0; l < 2; l++) {
                        if (sig_layer[filter_dim][i + k][j + l] > cur_max) {
                            max_i = i + k;
                            max_j = j + l;
                            cur_max = sig_layer[filter_dim][max_i][max_j];
                        }
                    }
                }
                max_pooling[filter_dim][max_i][max_j] = 1;
                max_layer[filter_dim][i / 2][j / 2] = cur_max;
            }
        }
    }
    //**No calculation, nothing need to be speed up, maybe load?
    int k = 0;
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 14; i++) {
            for (int j = 0; j < 14; j++) {
                dense_input[k] = max_layer[filter_dim][i][j];
                k++;
            }
        }
    }

    //** Dense Layer
    for (int i = 0; i < 120; i++){
        dense_sum[i] = 0;
        dense_sigmoid[i] = 0;
    }
///////////////////////////////Not done/////////////////////////////////
    //Memory is not continus
    for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 980; j++) {
            dense_sum[i] += dense_w[j][i] * dense_input[j];
        }
        dense_sum[i] += dense_b[i];// Only can speed up here
    }
//////////////////////////////Not done//////////////////////////////////
    //not sure whether can we speed up
    for (int i = 0; i < 120; i++) {
        dense_sigmoid[i] = sigmoid(dense_sum[i]);
    }

    // Dense Layer 2, Memory is not continus
    for (int i = 0; i < 10; i++) {
        dense_sum2[i] = 0;
        for (int j = 0; j < 120; j++) {
            dense_sum2[i] += dense_w2[j][i] * dense_sigmoid[j];
        }
        dense_sum2[i] += dense_b2[i];// Only can speed up here
    }

    // Softmax Output, , not sure whether can we speed up
    double den = softmax_den(dense_sum2, 10);
    for (int i = 0; i < 10; i++) {
        dense_softmax[i] = exp(dense_sum2[i]) / den;
    }
}

void update_weights() {
    __m256d a_local, b_local, result_local, mid_local; 
    double *mid_value;
    double learn_value = double(-1) * eta;
    double learn[4] = {learn_value,learn_value,learn_value,learn_value};
    double *a_start = NULL;
    double *b_start = NULL;
    double *c_strat = NULL;
    int n = 0;

    
    ////////////////// done dense_b /////////////////
    //dense_b[i] -= eta * db1[i];
    a_start = db1;
    b_start = learn;
    c_strat = dense_b;
    n = 0;
    for(; n < 120; n = n+4){
        a_local = _mm256_loadu_pd(a_start); 
        b_local = _mm256_loadu_pd(b_start); 
        result_local = _mm256_loadu_pd(c_strat); 

        mid_local = _mm256_mul_pd(a_local, b_local);
        result_local = _mm256_add_pd(result_local, mid_local);

        _mm256_storeu_pd(c_strat, result_local);

        a_start = a_start + 4;
        c_strat = c_strat + 4;
    }
    ////////////////// done dense_b2  /////////////////
    a_start = db2;
    b_start = learn;
    c_strat = dense_b2;
    n = 10;
    for(; n >=3; n = n-4){
        a_local = _mm256_loadu_pd(a_start); 
        b_local = _mm256_loadu_pd(b_start); 
        result_local = _mm256_loadu_pd(c_strat); 

        mid_local = _mm256_mul_pd(a_local, b_local);
        result_local = _mm256_add_pd(result_local, mid_local);

        _mm256_storeu_pd(c_strat, result_local);

        a_start = a_start + 4;
        c_strat = c_strat + 4;
    }

    for (; n > 0; n--){
        *c_strat++ -= *a_start++ + *b_start;
    }
    
    ////////////////// done dense_w2  /////////////////
    a_start = dw2[0];
    b_start = learn;
    c_strat = dense_w2[0];
    n = 0;
    for(; n < 1200; n = n+4){
        a_local = _mm256_loadu_pd(a_start); 
        b_local = _mm256_loadu_pd(b_start); 
        result_local = _mm256_loadu_pd(c_strat); 

        mid_local = _mm256_mul_pd(a_local, b_local);
        result_local = _mm256_add_pd(result_local, mid_local);

        _mm256_storeu_pd(c_strat, result_local);

        a_start = a_start + 4;
        c_strat = c_strat + 4;
    }

    ////////////////// done dense_w1  /////////////////
    a_start = dw1[0];
    b_start = learn;
    c_strat = dense_w[0];
    n = 0;
    for(; n < 120*980; n = n+4){
        a_local = _mm256_loadu_pd(a_start); 
        b_local = _mm256_loadu_pd(b_start); 
        result_local = _mm256_loadu_pd(c_strat); 

        mid_local = _mm256_mul_pd(a_local, b_local);
        result_local = _mm256_add_pd(result_local, mid_local);

        _mm256_storeu_pd(c_strat, result_local);

        a_start = a_start + 4;
        c_strat = c_strat + 4;
    }

    ////////////////// done conv_w /////////////////
    a_start = dw_conv[0][0];
    b_start = learn;
    c_strat = conv_w[0][0];
    n = 7 * 7 * 5;
    for(; n >= 3; n = n-4){
        a_local = _mm256_loadu_pd(a_start); 
        b_local = _mm256_loadu_pd(b_start); 
        result_local = _mm256_loadu_pd(c_strat); 

        mid_local = _mm256_mul_pd(a_local, b_local);
        result_local = _mm256_add_pd(result_local, mid_local);

        _mm256_storeu_pd(c_strat, result_local);

        a_start = a_start + 4;
        c_strat = c_strat + 4;
    }
    for (; n > 0; n--){
        *c_strat++ -= *a_start++ + *b_start;
    }


    ////////////////// done conv_b/////////////////
    a_start = db_conv[0][0];
    b_start = learn;
    c_strat = conv_b[0][0];
    n = 0;
    for(; n < 784 * 5; n = n+4){
        a_local = _mm256_loadu_pd(a_start); 
        b_local = _mm256_loadu_pd(b_start); 
        result_local = _mm256_loadu_pd(c_strat); 

        mid_local = _mm256_mul_pd(a_local, b_local);
        result_local = _mm256_add_pd(result_local, mid_local);

        _mm256_storeu_pd(c_strat, result_local);

        a_start = a_start + 4;
        c_strat = c_strat + 4;
    }
        
    ////////////////// done /////////////////
    
}
/* ************************************************************ */

/* ************************************************************ */
/* Backward Pass */
void backward_pass(double *y_hat, int *y, int img[][32]) {
    // can spped up
    double delta4[10];
    for (int i = 0; i < 10; i++) {
        delta4[i] = y_hat[i] - y[i];   // Derivative of Softmax + Cross entropy
        db2[i] = delta4[i];            // Bias Changes
    }

    // Calculate Weight Changes for Dense Layer. construct a new array for dense_sigmoid
    for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 10; j++) {
            dw2[i][j] = dense_sigmoid[i] * delta4[j];
        }
    }

    // Delta 3
    // Problem1 is delta3 only have 1 value need to be change
    // d_sigmoid can construct a new array
    double delta3[120];
    for (int i = 0; i < 120; i++) {
        delta3[i] = 0;
        for (int j = 0; j < 10; j++) {
            delta3[i] += dense_w2[i][j] * delta4[j];
        }
        delta3[i] *= d_sigmoid(dense_sum[i]);
    }
    for (int i = 0; i < 120; i++) db1[i] = delta3[i];   // Bias Weight change

    // Calculate Weight Changes for Dense Layer 1
    for (int i = 0; i < 980; i++) {
        for (int j = 0; j < 120; j++) {
            dw1[i][j] = dense_input[i] * delta3[j];
        }
    }

    // Delta2, same proble as in Delta3
    double delta2[980];
    for (int i = 0; i < 980; i++) {
        delta2[i] = 0;
        for (int j = 0; j < 120; j++) {
            delta2[i] += dense_w[i][j] * delta3[j];
        }
        delta2[i] *= d_sigmoid(dense_input[i]);
    }

    //** Calc back-propagated max layer dw_max, no need to spped up
    int k = 0;
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 28; i += 2) {
            for (int j = 0; j < 28; j += 2) {
                for (int l = 0; l < 2; l++) {
                    for (int m = 0; m < 2; m++) {
                        if (max_pooling[filter_dim][i + l][j + m] == 1)
                            dw_max[filter_dim][i][j] = delta2[k];
                        else
                            dw_max[filter_dim][i][j] = 0;
                    }
                }
                k++;
            }
        }
    }
    //** Calc Conv Bias Changes, no need to spped up
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                db_conv[filter_dim][i][j] = dw_max[filter_dim][i][j];
            }
        }
    }

    //** Set Conv Layer Weight changes to 0, no need to spped up
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                dw_conv[filter_dim][i][j] = 0;
            }
        }
    }

    // The problem here is we can't start at img[-2][-2]
    // Calculate Weight Changes for Conv Layer
    for (int filter_dim = 0; filter_dim < 5; filter_dim++) {
        for (int i = 0; i < 28; i++) {
            for (int j = 0; j < 28; j++) {
                double cur_val = dw_max[filter_dim][i][j];
                for (int k = 0; k < 5; k++) {
                    for (int l = 0; l < 5; l++) {
                        dw_conv[filter_dim][k][l] += img[i - 2 + k][j - 2 + l] * cur_val;
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
    if (csvread) {
        string s;
        int data_pt = 0;
        while (getline(csvread, s)) {
            stringstream ss(s);
            int pxl = 0;
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                if (pxl == 0) {
                    label_train[data_pt] = stoi(substr);
                } else {
                    data_train[data_pt][pxl - 1] = stoi(substr);
                }
                pxl++;
            }
            data_pt++;
        }
        csvread.close();
    } else {
        cerr << "Unable to read train data!" << endl;
        exit(EXIT_FAILURE);
    }
}
void read_test_data() {
    ifstream csvread;
    csvread.open("/cad2/ece1718s/mnist_test.csv", ios::in);
    if (csvread) {
        string s;
        int data_pt = 0;
        while (getline(csvread, s)) {
            stringstream ss(s);
            int pxl = 0;
            while (ss.good()) {
                string substr;
                getline(ss, substr, ',');
                if (pxl == 0) {
                    label_test[data_pt] = stoi(substr);
                } else {
                    data_test[data_pt][pxl - 1] = stoi(substr);
                }
                pxl++;
            }
            data_pt++;
        }
        csvread.close();
    } else {
        cerr << "Unable to read test data!" << endl;
        exit(EXIT_FAILURE);
    }
}

void give_img(int *vec, int img[][32]) {
    int k = 0;
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 32; j++) {
            if (i < 2 || j < 2) {
                img[i][j] = 0;
            } else {
                img[i][j] = vec[k];
                k++;
            }
        }
    }
}

void give_y(int y, int *vector_y) {
    for (int i = 0; i < 10; i++) vector_y[i] = 0;
    vector_y[y] = 1;
}
int give_prediction() {
    double max_val = dense_softmax[0];
    int max_pos = 0;
    for (int i = 1; i < 10; i++) {
        if (dense_softmax[i] > max_val) {
            max_val = dense_softmax[i];
            max_pos = i;
        }
    }

    return max_pos;
}

int main() {
    //cout << "Data footprint: " << sizeof(data_footprint) << endl;
    read_test_data();
    read_train_data();
    initialise_weights();

    int epoch = 500;
    int num = 0;
    cout << "Start Training." << endl;
    for (int i = 0; i < epoch; i++) {
        cout << "Epoch " << i << " done." << endl;
        for (int j = 0; j < batch_size; j++) {
            num = rand() % 60000;
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
    int cor = 0;
    int confusion_mat[10][10];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) confusion_mat[i][j] = 0;
    }

    cout << "Start Testing." << endl;
    for (int i = 0; i < val_len; i++) {
        int img[32][32];
        give_img(data_test[i], img);
        forward_pass(img);
        int pre = give_prediction();
        confusion_mat[label_test[i]][pre]++;
        if (pre == label_test[i]) cor++;
    }
    double accu = double(cor) / val_len;
    cout << "Accuracy: " << accu << endl;

    cout << "   0 1 2 3 4 5 6 7 8 9" << endl;
    for (int i = 0; i < 10; i++) {
        cout << i << ": ";
        for (int j = 0; j < 10; j++) {
            cout << confusion_mat[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
