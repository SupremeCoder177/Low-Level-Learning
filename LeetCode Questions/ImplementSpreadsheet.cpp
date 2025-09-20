#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <math.h>

class SpreadSheet{

    private:
    int* arr;
    int row_size;
    int size;

    int get_col(std::string cell){
        char col = cell[0];
        return (int) std::tolower(col) - (int) 'a';
    }

    int get_row(std::string cell){  
        std::vector<char> chars;

        for(int i = 1; i < cell.length(); i++){
            chars.push_back(cell[i]);
        }

        int output = 0;
        for(int i = 0; i < chars.size(); i++){
            output += pow(10, chars.size() - (i + 1)) * ((int) chars[i] - (int) '0');
        }
        return output - 1;
    }

    void get_start_and_offset(std::string cell, int* storage){
        storage[0] = get_row(cell);
        storage[1] = get_col(cell);
    }

    int get_cell_values(std::string cell){
        int* temp = new int[2];
        get_start_and_offset(cell, temp);
        int val = arr[temp[0] * row_size + temp[1]];
        delete[] temp;
        return val;
    }

    int parse_string_to_int(std::string num){
        int output = 0;
        for(int i = 0; i < num.size(); i++){
            output += pow(10, num.size() - (i + 1)) * ((int) num[i] - (int) '0');
        }
        return output;
    }

    public:

    SpreadSheet(int rows){        
        size = 26 * rows;
        arr = new int[size];
        row_size = 26;

        for(int i = 0; i < size; i++){
            arr[i] = 0;
        }
    }

    ~SpreadSheet(){
        delete[] arr;
    }

    void setCell(std::string cell, int value ){
        int temp[2];
        get_start_and_offset(cell, temp);
        arr[temp[0] * row_size + temp[1]] = value;
    }

    void resetCell(std::string cell){
        int temp[2];
        get_start_and_offset(cell, temp);
        arr[temp[0] * row_size + temp[1]] = 0;
    }

    int getValue(std::string formula){
        int output = 0;
        int index = 1;
        std::vector<char> chars;
        char operators[] = {'+', '-', '*', '/'};
        char curr_operator;
        bool first_num = true;
        bool cell = false;
        while(index < formula.length()){
            chars.clear();
            int tmp = (int) std::tolower(formula[index]);
            if(tmp >= 'a' && tmp <= 'z'){
                cell = true;   
            }
            while (index < formula.length()){   
                bool end = false;
                for(char ch : operators){
                    if(ch == formula[index]) {
                        end = true;
                        curr_operator = formula[index];
                        break;
                    }
                }
                if(end) break;
                chars.push_back(formula[index]);
                index++;
            }
            
            std::string str(chars.begin(), chars.end());
            if(first_num){
                if(cell){
                    output = get_cell_values(str);
                }else{
                    output = parse_string_to_int(str);
                }
                first_num = false;
            }else{
                int val;
                if(cell){
                    val = get_cell_values(str);
                }else{
                    val = parse_string_to_int(str);
                }

                switch (curr_operator)
                {
                case '+':
                    output += val;
                    break;
                case '-':
                    output -= val;
                    break;
                case '*':
                    output *= val;
                    break;
                default:
                    if(val != 0) output /= val;
                    break;
                }
            }
            index++;
            cell = false;
        }
        return output;
    }
};

int main(){
    
    SpreadSheet sheet(45);
    sheet.setCell("A1", 12);
    int val = sheet.getValue("=A1+4");
    std::cout << val << std::endl;

    return 0;
}