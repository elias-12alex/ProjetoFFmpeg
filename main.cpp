/* 
    Projeto Prometheus
    Curso de C++ 
    Atividade de Reprodução de vídeo usando o ffmpeg
    @autor Elias Alexander Santos

*/
/*
    Para a realização do trabalho foi necessário a instalação do FFmpeg, baixei tanto pelo windows quanto pelo ubuntu para realizar os testes. Utilizei o vccode como editor de código padrão como foi aconselhado pelo professor.
    No trabalho só tive um pouco de dificuldade para conseguir reproduzir o vídeo utilizando as bibliotecas do ffmpeg em c++, porém percebi que não havia tanta necessidade pois dava para reproduzir o vídeo sem utilizar as devidas bibliotecas. Feito isso, foquei nas melhorias do programa e no codec. 
    
    obs: O vídeo utilizado é um vídeo de 2min que baixei da internet para realizar o trabalho.

*/

//bibliotecas padrão do c++
#include <iostream> 
#include <cstdlib>

using namespace std; //faz com que não seja necessário utilizar o std no código

/*
// biblioteca do FFmpeg porém não foi necessário
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
}*/

int main() { //função principal onde acontece a execução dos comandos de reprodução dos vídeos
    
    //av_register_all();     //código para inicializar o FFmpeg 

    string videoPath = "../Historia.mp4"; //localizando o caminho original do vídeo que eu quero reproduzir
    string command = "ffplay -i " + videoPath ; //Novo caminho do vídeo pelo ffplay
    int result = system(command.c_str()); //cria uma variável chamada result, que armazenará o comando que executaremos no terminal
    if (result != 0) { //Se o resultado for diferente de zero, significa que ocorreu um erro ao reproduzir o vídeo e imprime uma mensagem de erro.
        cout << "Erro ao reproduzir o video." << endl;
        return -1;
    }

    /*  Comandos para terminar o vídeo e dá o break, porém não funcionou 
    string killCommand = "pkill -f ffplay"; 
    system(killCommand.c_str());
    */

    string command2 = "ffprobe -v error -select_streams v:0 -show_entries stream=codec_name -of default=noprint_wrappers=1:nokey=1 " + videoPath; //Comando para obter o codec do vídeo pelo ffprobe

    cout << "Executando o comando: " << command2 << endl; //Imprime o comando utilizado

    string result_codec; //variável de codec do vídeo 

    FILE* pipe = popen(command2.c_str(), "r"); // Executa o comando e obtém um pipe para ler ("r") a saída do processo
    
    if (!pipe) {
        cout << "Erro ao executar o comando." << endl; 
        return -1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result_codec += buffer;         // Lê as linhas da saída do comando e add ao conteúdo da variável "result_codec"
    }

    pclose(pipe); //Fecha o pipe

    cout << "Codec de video: " << result_codec; //Imprime o nome do Codec de vídeo, que no caso é h264

    return 0; 
}

/*  Demais comandos do FFmpeg
    AVCodecContext* codecContext = avcodec_alloc_context3(codec); //Inicializando o decodificador de vídeo
    avformat_close_input(&formatContext); //liberar a memória alocada e fechar os recursos do FFmpeg
    avformat_network_deinit();
}*/
