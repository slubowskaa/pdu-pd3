#include <iostream>
#include <fstream>

using namespace std;

//Szacowanie z góry liczby użytkowników forum na którym liczę posty.
#define USERS_COUNT 280000


bool is_active_user[USERS_COUNT];
int number_of_questions[USERS_COUNT];
int number_of_answers[USERS_COUNT];
//Uzupełniam wartości startowe tablic.
void dataInit(){
    for(int i=0;i<USERS_COUNT;i++){
        number_of_answers[i] = 0;
        number_of_questions[i] = 0;
        is_active_user[i] = false;
    }
}

void loadData(string INPUT_POSTS, string INPUT_USERS){
    int id,it;
    string line;

    //Wczytuję informacje o postach.
    ifstream file(INPUT_POSTS);
    if(file.is_open()){
        //Muszę zignorować linię zawierającą nazwy kolumn.
        getline(file,line);
        while(getline(file,line)){
            id = 0;
            it = 0;

            //Wczytuję znak po znaku pierwszą liczbę, aż dojdę do przecinka.
            while(line[it] != ','){
                if(line[it] < '0' || line[it] > '9')
                    cerr << "Błędny znak w danych\n";
                else{
                    id *= 10;
                    id += (int)(line[it] - '0');
                }
                it++;
            }

            if(line[line.length()-1] == '1') number_of_questions[id]++;
            else if(line[line.length()-1] == '2') number_of_answers[id]++;
            else cerr << "Błędny znak w danych\n";
        }
        file.close();
    }
    else cout << "Nie udało się otworzyć pliku.";

    //Uzupełniam dane o poprawnych id użytkowników.
    ifstream file2(INPUT_USERS);
    if(file2.is_open()){
        //Muszę zignorować linię zawierającą nazwy kolumn.
        getline(file2,line);
        while(getline(file2,line)){
            id = 0;
            it = 0;
            //Wczytuję znak po znaku id użytkownika.
            while(it < line.length()){
                if(line[it] < '0' || line[it] > '9')
                    cerr << "Błędny znak w danych\n";
                else{
                    id *= 10;
                    id += (int)(line[it] - '0');
                }
                it++;
            }
            //Zapisuję, że dane id należy do aktywnego użytkownika.
            is_active_user[id] = true;
        }
        file2.close();
    }
    else cout << "Nie udało się otworzyć pliku.";
}

void saveData(string OUTPUT_CSV){
    ofstream file(OUTPUT_CSV);
    if(file.is_open()){
        file << "Id,NumberOfQuestions,NumberOfAnswers\n";
        for(int i=0;i<USERS_COUNT;i++)
            if(is_active_user[i]){
                file << i << "," << number_of_questions[i] << "," <<
                    number_of_answers[i] << "\n";
            }
        file.close();
    }
    else cout << "Nie udało się otworzyć pliku.";
}

int main(int argc, char *argv[]){
    //"Magiczna linijka."
    ios_base::sync_with_stdio(0);

    string input_posts = "";
    string input_users = "";
    string output_csv = "";
    // Argumenty programu
    if (argc != 4) {
        cout << "Niepoprawne parametry programu";
        return 0;
    } else {
        input_posts = argv[1];
        input_users = argv[2];
        output_csv = argv[3];
        cout << input_posts << endl;
        cout << input_users << endl;
        cout << output_csv;
    }

    dataInit();
    loadData(input_posts, input_users);
    saveData(output_csv);

    return 0;
}
