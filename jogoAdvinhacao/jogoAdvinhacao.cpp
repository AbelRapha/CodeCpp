#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std; // Habilita o cout

int main (){

    cout << "**********************\n" ;
    cout << "Bem- vindos ao jogo de adivinhação!!\n" ;
    cout << "**********************\n\n";

    cout << "Escolha o seu nível de dificuldade: \n";
    cout << "Fácil (F),  Médio(M) ou Difícil (D)?\n";

    char dificuldade;
    cin >> dificuldade;

    int numero_tentativas;
    
    if (dificuldade == 'F'){
        numero_tentativas = 15;
    }
    else if(dificuldade == 'M'){
        numero_tentativas = 5;
    }
    else{
        numero_tentativas = 2;
    }

    srand(time(NULL));
    const int NUMERO_SECRETO = rand()%100;
    int tentativas = 0;
    bool nao_acertou = true;
    double pontos = 1000.0;
    bool tentativas_excedidas = false;

    while(nao_acertou && tentativas_excedidas == false){
        tentativas++;
        cout << "Tentativa nº " << tentativas << endl;
        int chute;
        cout << "Qual o seu chute? R: ";
        cin >> chute;

        double pontos_perdidos = abs(chute - NUMERO_SECRETO)/2.0;
        pontos = pontos - pontos_perdidos;
        tentativas_excedidas = tentativas >= numero_tentativas;

        cout << "O valor do seu chute é: " << chute << endl;

        bool acertou = chute == NUMERO_SECRETO;
        bool maior = chute > NUMERO_SECRETO;

        if (acertou){
        cout << "Parabéns!! Você acertou o número secreto!!\n";
        nao_acertou = false;
    }

    else if (maior){
        cout << "Seu chute foi maior que o número secreto!\n";
    }

    else{
        cout << "Seu chute foi menor que o número secreto\n";
    }
    }
    cout << "\nFIM DO JOGO\n";

    if (nao_acertou){
        cout << "Você perdeu! Você esgotou sua quantidade de tentativas\n";
        cout << "Sua pontuação foi de: " << pontos << "pontos.\n";
        cout << "Tente novamente.\n";
    }
    else{
        cout << "Você ganhou, o número de tentativas necessárias foi: " << tentativas << " tentativas.\n";
        cout.precision(2);
        cout << fixed;
        cout << "Sua pontuação foi de "<< pontos << " pontos.\n";
    }
    

    return 0;

}