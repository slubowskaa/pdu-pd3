#include <iostream>
#include <fstream>
using namespace std;
//Szacowanie z góry liczby użytkowników forum na którym zapuszczam F&U.
#define USERS_COUNT 280000

int repr[USERS_COUNT];
int tree_size[USERS_COUNT];
bool is_active_user[USERS_COUNT];
//Uzupełniam wartości startowe tablic.
void dataInit(){
    for(int i=0;i<USERS_COUNT;i++){
        repr[i] = i;
        tree_size[i] = 1;
        is_active_user[i] = false;
    }
}
//FUNKCJE F&U:
//Find z optymalizacją kompresji.
int findRepr(int x){
    if(repr[x] == x) return x;
    repr[x] = findRepr(repr[x]);
    return repr[x];
}
//Union z delikatnie zmienioną optymalizacją.
//Zamiast uwzględniania "rank", łączę z uwzględnieniem liczności
//zbiorów, gdyż później i tak bym chciał je policzyć.
void unionVertices(int v1,int v2){
    int repr1 = findRepr(v1);
    int repr2 = findRepr(v2);
    if(repr1 == repr2) return;
    //Ustawiam zmienne reprezentantów tak, by podłączać repr2 do repr1.
    if(tree_size[repr1] < tree_size[repr2]){
        int tmp = repr1;
        repr1 = repr2;
        repr2 = tmp;
    }
    repr[repr2] = repr1;
    //Aktualizuję treesize, by zawsze było dokładnie policzone dla
    //wierzchołków będących reprezentantami.
    tree_size[repr1] += tree_size[repr2];
}
//Metoda przerabiająca dane o krawędziach w grafie użytkowników na
//strukturę F&U.
void loadEdges(string input_edges){
    int v1,v2,it;
    string line;
    ifstream file(input_edges);
    if(file.is_open()){
        //Muszę zignorować linię zawierającą nazwy kolumn.
        getline(file,line);
        while(getline(file,line)){
            v1 = 0;
            v2 = 0;
            it = 0;
            //Wczytuję znak po znaku pierwszą liczbę, aż dojdę do przecinka.
            while(line[it] != ','){
                if(line[it] < '0' || line[it] > '9')
                    cerr << "Błędny znak w danych\n";
                else{
                    v1 *= 10;
                    v1 += (int)(line[it] - '0');
                }
                it++;
            }
            //Pomijam przecinek.
            it++;
            //Wczytuję znak po znaku drugą liczbę z pozostałej części linijki.
            while(it < line.length()){
                if(line[it] < '0' || line[it] > '9')
                    cerr << "Błędny znak w danych\n";
                else{
                    v2 *= 10;
                    v2 += (int)(line[it] - '0');
                }
                it++;
            }
            //Aktualizuję strukturę F&U o połączenie między v1 i v2.
            unionVertices(v1,v2);
        }
        file.close();
    }
    else cout << "Nie udało się otworzyć pliku.";
}
//Metoda ładująca dane o poprawnych id użytkowników.
void loadVertices(string input_vertices){
    int id,it;
    string line;
    ifstream file(input_vertices);
    if(file.is_open()){
        //Muszę zignorować linię zawierającą nazwy kolumn.
        getline(file,line);
        while(getline(file,line)){
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
        file.close();
    }
    else cout << "Nie udało się otworzyć pliku.";
}
//Metoda kompresująca dane ze struktury F&U do formy do dalszej analizy.
//Mogę sobie pozwolić na to, bo wciąż ma to złożoność lepszą niż v*logv.
void compressTree(){
    for(int i=0;i<USERS_COUNT;i++){
        repr[i] = findRepr(i);
        tree_size[i] = tree_size[repr[i]];
    }
}
//Bonusowa metoda, zliczająca liczbę społeczności i zwracająca na wyjście
//standardowe trochę wstępnych informacji o nich.
void countCommunities(){
    int community_count = 0;
    int loner_count = 0;
    for(int i=0;i<USERS_COUNT;i++){
        if(repr[i] == i && is_active_user[i]){
            community_count++;
            if(tree_size[i] > 1)
                cout << "repr: " << i << " popul: " << tree_size[i] << "\n";
            else loner_count++;
        }
    }
    cout << "Total number of communities: " << community_count <<
        "(including " << loner_count << " isolated users)\n";
}
void saveData(string output_csv){
    ofstream file(output_csv);
    if(file.is_open()){
        file << "Id,Representative,GroupPopulation\n";
        for(int i=0;i<USERS_COUNT;i++)
            if(is_active_user[i])
                file << i << "," << repr[i] << "," << tree_size[i] << "\n";
        file.close();
    }
    else cout << "Nie udało się otworzyć pliku.";
}
int main(int argc, char *argv[]){
    //"Magiczna linijka."
    ios_base::sync_with_stdio(0);

    string input_edges = "";
    string input_vertices = "";
    string output_csv = "";
    // Argumenty programu
    if (argc != 4) {
        cout << "Niepoprawne parametry programu";
        return 0;
    } else {
        input_edges = argv[1];
        input_vertices = argv[2];
        output_csv = argv[3];
        cout << input_edges << endl;
        cout << input_vertices << endl;
        cout << output_csv;
    }
    dataInit();
    loadEdges(input_edges);
    loadVertices(input_vertices);
    compressTree();
    countCommunities();
    saveData(output_csv);
    return 0;
}
