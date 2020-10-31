#include "AutoDiff/AutoDiff.hpp"
#include <string>

// ===============================================================================
// You could change the type of console output by changing the mode variable!
// You could also change the mode in the middle of testing!
// when mode is equal to 0, it will output all tests' results
// when mode is equal to 1, it will output only the failed tests
// when model is equal to 2, it will throw an error if one of the test failed, will not print if the test has passed 
// when model is equal to 3, show no output / error at all (for unwanted printing)
// when mode is equal to 4, it won't show the description. It will only show if it is right or if it is wrong
// If you see a bar of green, then that means that every test was successful!
// any mode that is above 3 will throw an error
// ===============================================================================

int mode = 4; 

void TEST (bool val, string description) {
    if (mode > 4) {
        throw invalid_argument("invalid mode");
    }
    string red = "\033[1;31m";
    string green = "\033[1;32m";
    string desc = "\033[0;36m";
    string normal = "\033[0m";
    string desc_title = "\033[0;34m";
    string green_back = "\033[0;42m";
    string red_back = "\033[0;41m";
    if (val) {
        if (mode == 0) {
            cout<<green<<"TEST PASSED!"<<desc<<" DESCRIPTION: "<<desc_title<<description<<normal<<endl; 
        } else if (mode == 4) {
            cout<<green_back<<" "<<normal;
        }
    } else {
        if (mode == 1 ||  mode == 0) {
            cout<<red<<"TEST FAILED!"<<desc<<" DESCRIPTION: "<<desc_title<<description<<normal<<endl; 
        } 
        else if (mode == 2) {
            string error = red + "TEST FAILED!" + desc + " DESCRIPTION: " + desc_title + description + normal;
            throw invalid_argument(error);  
        } else if (mode == 4) {
            cout<<red_back<<" "<<normal;
        }
    }
}

int main () {
    // to run: 
    // c++ -std=c++11 -I AutoDiff/Headers/ AutoDiff/src/Variable/* AutoDiff/src/Vector/* test.cpp && ./a.out && rm a.out
    system("clear");
    Variable x;
    Variable y;
    Variable z; 
    // =======================================
    // VARIABLE OPERATIONS EVALUATING
    // =======================================

    TEST((x + 3).eval({2}) == 5, "eval: Adding variable and double");
    TEST((3 + x).eval({2}) == 5, "eval: Adding double and variable"); 
    TEST((x + y).eval({3,2}) == 5, "eval: Variable and Variable");

    TEST((x - 3).eval({2}) == -1, "eval: Subtracting variable and double");
    TEST((3 - x).eval({2}) == 1, "eval: Subtracting double and variable"); 
    TEST((x - y).eval({3,2}) == 1, "eval: Subtracting Variable and Variable");

    TEST((x * 3).eval({2}) == 6, "eval: Multiplying variable and double");
    TEST((3 * x).eval({2}) == 6, "eval: Multiplying double and variable"); 
    TEST((x * y).eval({3,2}) == 6, "eval: Multiplying Variable and Variable");

    TEST((x / 3).eval({2}) == (double(2)/3), "eval: Dividing variable and double");
    TEST((3 / x).eval({2}) == (double(3)/2), "eval: Dividing double and variable"); 
    TEST((x / y).eval({3,2}) == (double(3)/2), "eval: Dividing Variable and Variable");

    TEST((x ^ 3).eval({2}) == 8, "eval: Exponent variable and double");
    TEST((3 ^ x).eval({2}) == 9, "eval: Exponent double and variable"); 
    TEST((x ^ y).eval({3,2}) == 9, "eval: Exponent Variable and Variable");
    
    TEST(min_op(x, y).eval({5,12}) == 5, "eval: Min operation Variable and Variable");
    TEST(min_op(5, y).eval({12}) == 5, "eval: Min operation double and Variable");
    TEST(min_op(x, 1).eval({5}) == 1, "eval: Min operation Variable and double"); 

    TEST(max_op(x, y).eval({5,12}) == 12, "eval: Max operation Variable and Variable");
    TEST(max_op(5, y).eval({12}) == 12, "eval: Max operation double and Variable");
    TEST(max_op(x, 1).eval({5}) == 5, "eval: Max operation Variable and double"); 

    TEST(x.clip(-1, 4).eval({-6}) == -1, "eval: clipping input (double & double). Input reaches lower bounds");
    TEST(x.clip(-1, 4).eval({7}) == 4, "eval: clipping input (double & double). Input reaches upper bounds");   
    TEST(x.clip(-1, 4).eval({3}) == 3, "eval: clipping input (double & double). Input within bound");   
    
    TEST(x.clip(y, 4).eval({-1, -6}) == -1, "eval: clipping input (variable & double). Input reaches lower bounds");
    TEST(x.clip(y, 4).eval({6, 1}) == 4, "eval: clipping input (variable & double) Input reaches upper bounds");   
    TEST(x.clip(y, 4).eval({-1, 3}) == 3, "eval: clipping input (variable & double) Input within bound");   

    TEST(x.clip(-4, y).eval({-7, -2}) == -4, "eval: clipping input (double & variable). Input reaches lower bounds");
    TEST(x.clip(-4, y).eval({-1, 7}) == -1, "eval: clipping input (double & variable) Input reaches upper bounds");   
    TEST(x.clip(-4, y).eval({-1, -2}) == -2, "eval: clipping input (double & variable) Input within bound");   

    TEST(x.clip(y,z).eval({-8, -5, -3}) == -5, "eval: clipping input (double & double). Input reaches lower bounds");    
    TEST(x.clip(y,z).eval({-5, -2, 3}) == -2, "eval: clipping input (double & double). Input reaches upper bounds");    
    TEST(x.clip(y,z).eval({-4, -5, -2}) == -4, "eval: clipping input (double & double). Input within bounds");    

    // =======================================
    // VARIABLE OPERATIONS GRAD
    // =======================================

    TEST((x + 3).grad({2})[0] == 5, "grad: Adding variable and double");
    TEST((3 + x).grad({2})[0] == 5, "grad: Adding double and variable"); 
    TEST((x + y).grad({3,2})[0] == 5, "grad: Variable and Variable");

    TEST((x - 3).grad({2})[0] == -1, "grad: Subtracting variable and double");
    TEST((3 - x).grad({2})[0] == 1, "grad: Subtracting double and variable"); 
    TEST((x - y).grad({3,2})[0] == 1, "grad: Subtracting Variable and Variable");

    TEST((x * 3).grad({2})[0] == 6, "grad: Multiplying variable and double");
    TEST((3 * x).grad({2})[0] == 6, "grad: Multiplying double and variable"); 
    TEST((x * y).grad({3,2})[0] == 6, "grad: Multiplying Variable and Variable");

    TEST((x / 3).grad({2})[0] == (double(2)/3), "grad: Dividing variable and double");
    TEST((3 / x).grad({2})[0] == (double(3)/2), "grad: Dividing double and variable"); 
    TEST((x / y).grad({3,2})[0] == (double(3)/2), "grad: Dividing Variable and Variable");

    TEST((x ^ 3).grad({2})[0] == 8, "grad: Exponent variable and double");
    TEST((3 ^ x).grad({2})[0] == 9, "grad: Exponent double and variable"); 
    TEST((x ^ y).grad({3,2})[0] == 9, "grad: Exponent Variable and Variable");
    
    TEST(min_op(x, y).grad({5,12})[0] == 5, "grad: Min operation Variable and Variable");
    TEST(min_op(5, y).grad({12})[0] == 5, "grad: Min operation double and Variable");
    TEST(min_op(x, 1).grad({5})[0] == 1, "grad: Min operation Variable and double"); 

    TEST(max_op(x, y).grad({5,12})[0] == 12, "grad: Max operation Variable and Variable");
    TEST(max_op(5, y).grad({12})[0] == 12, "grad: Max operation double and Variable");
    TEST(max_op(x, 1).grad({5})[0] == 5, "grad: Max operation Variable and double"); 

    TEST(x.clip(-1, 4).grad({-6})[0] == -1, "grad: clipping input (double & double). Input reaches lower bounds");
    TEST(x.clip(-1, 4).grad({7})[0] == 4, "grad: clipping input (double & double). Input reaches upper bounds");   
    TEST(x.clip(-1, 4).grad({3})[0] == 3, "grad: clipping input (double & double). Input within bound");   
    
    TEST(x.clip(y, 4).grad({-1, -6})[0] == -1, "grad: clipping input (variable & double). Input reaches lower bounds");
    TEST(x.clip(y, 4).grad({6, 1})[0] == 4, "grad: clipping input (variable & double) Input reaches upper bounds");   
    TEST(x.clip(y, 4).grad({-1, 3})[0] == 3, "grad: clipping input (variable & double) Input within bound");   

    TEST(x.clip(-4, y).grad({-7, -2})[0] == -4, "grad: clipping input (double & variable). Input reaches lower bounds");
    TEST(x.clip(-4, y).grad({-1, 7})[0] == -1, "grad: clipping input (double & variable) Input reaches upper bounds");   
    TEST(x.clip(-4, y).grad({-1, -2})[0] == -2, "grad: clipping input (double & variable) Input within bound");   

    TEST(x.clip(y,z).grad({-8, -5, -3})[0] == -5, "grad: clipping input (double & double). Input reaches lower bounds");    
    TEST(x.clip(y,z).grad({-5, -2, 3})[0] == -2, "grad: clipping input (double & double). Input reaches upper bounds");    
    TEST(x.clip(y,z).grad({-4, -5, -2})[0] == -4, "grad: clipping input (double & double). Input within bounds");    

    // =======================================
    // VECTOR OPERATIONS
    // =======================================

    Vector a = Vector(2);
    Vector b = Vector(2); 
    a = {x, y};
    b = {z, x};
    Vector result = (a+b).eval({1,3,4});
    double result_one = result.array[0].value;
    double result_two = result.array[1].value;
    TEST(result_one == 4 && result_two == 5, "eval: vector addition Vector & Vector");
    // =======================================
    // VECTOR & VARIABLE & MULTIPLE OPERATIONS
    // =======================================

    if (mode == 4) {
        cout<<endl; 
    }
    
}