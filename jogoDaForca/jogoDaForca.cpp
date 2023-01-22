#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>


using namespace std;

string palavra_secreta;
map<char, bool> chutou;
vector<char> chutes_errados;

vector<string> ler_arquivo(){
    ifstream arquivo;

    arquivo.open("listapalavras.txt");

    if (arquivo.is_open()){

        int quantidade_palavras;
        arquivo >> quantidade_palavras;
        cout << "O arquivo possui " << quantidade_palavras << endl;

        vector<string> palavras_do_arquivo;

        for (int i = 0; quantidade_palavras > i ; i++){
            string palavra_lida;
            arquivo >> palavra_lida;
            cout << "Na linha " << i << ": "<< palavra_lida << endl;
            palavras_do_arquivo.push_back(palavra_lida);
        }
        
        arquivo.close();
        
        return palavras_do_arquivo;
    }

    else{
        cout << "NÆo foi poss¡vel abrir o arquivo do banco de palavras\n";
        exit(0);
    }
}

void sorteia_palavra(){
    vector<string> palavras = ler_arquivo();

    srand(time(NULL));
    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];

}

bool letra_existe(char chute){
    for (char letra : palavra_secreta){
        bool contem_letra = chute == letra;
        if(contem_letra){
            return true;
        }
    }
    return false;
}

bool nao_acertou(){
    for (char letra : palavra_secreta){
        if(!chutou[letra]){
            return true;
        }
    }
    return false;
}

bool nao_enforcou(){
    return chutes_errados.size() < palavra_secreta.size();
}

void cabecalho(){
    cout << "**************************\n";
    cout << "       JOGO DA FORCA      \n";
    cout << "**************************\n";
}

void erros(){
    cout << "Chutes errados: ";
        for(char letra : chutes_errados){
            cout << letra <<  " ";
        }

    cout << endl;
}

void imprime_palavra_secreta(){
    for(char letra : palavra_secreta){
            bool ja_chutou = chutou[letra];
            if(ja_chutou){
                cout << letra << " ";
                
            }
            else{
                cout << "_ ";
            }
        }
}

void resultado_chute(){

    cout << "\n\nDigite uma letra: ";
    char chute;
    cin >> chute;

    chutou[chute] = true;

    bool acertou_letra = letra_existe(chute);

    if(acertou_letra){
        cout << "Vocˆ acertou!! Seu chute est  na palavra.\n";
    }

    else{
        cout << "Vocˆ errou!! Essa letra nÆo est  nessa palavra.\n";
        chutes_errados.push_back(chute);
    }
}

void salva_arquivo(vector<string> nova_lista){
    ofstream arquivo;
    arquivo.open("listapalavras.txt");

    if(arquivo.is_open()){

        arquivo << nova_lista.size() << endl;
        for (string palavra : nova_lista){
            arquivo << palavra << endl;
        }

    }
    else{
        cout << "Arquivo nÆo encontrado\n";
        exit(0);
    }

}

void adiciona_palavra(){
    cout << "Adicione uma nova palavra: ";
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = ler_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);

}

void finaliza_jogo(){
    cout << "FIM DE JOGO!!\n";

    if(nao_acertou()){
        cout << "Que pena!! DEU FORCA!!\n";
        cout << "Tente novamente\n";
    }
    else{
        cout << "PARABNS!! Vocˆ venceu. A palavra secreta era: " << palavra_secreta << endl;

        cout << "Vocˆ deseja adicionar uma nova palavra ao banco? (S/N)\n";

        char resposta;
        cin >> resposta;

        if(resposta == 'S'){
            adiciona_palavra();
            ler_arquivo();
            cout << "Volte sempre :)\n";

        }
        else{
            cout << "Ok, volte sempre :)\n";
        }

    }
}

int main(){
    cabecalho();

    ler_arquivo();

    sorteia_palavra();

    while (nao_enforcou() && nao_acertou())
    {
        erros();

        imprime_palavra_secreta();
        
        resultado_chute();
    }
    
    finaliza_jogo();
    
}