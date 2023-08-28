#ifndef CRIADORPROJETOCPP_HPP
#define CRIADORPROJETOCPP_HPP

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include <sys/stat.h>


#ifdef _WIN32
    #include <direct.h> // Para Windows
#else
    #include <sys/types.h>
    #include <unistd.h>  // Para sistemas baseados em POSIX, como Linux
#endif

class CriadorProjetoCpp{
    private:
        bool carregar(); // Carrega As Variaveis;
        bool verificaCarregar(); // Verifica Se Foi Carregado
        bool criarPastaProjeto(); // Cria A Pasta Projeto;
        bool criarPastaSrc(); // Cria A Pasta Src;
        bool criarArquivosSrc(); // Cria Os Arquivos Da Pasta Src;
        bool criarPastaInclude(); // Cria As Pasta Include;
        bool criarArquivosInclude(); // Cria Os Arquivos Da Pasta Include;
        bool criarArquivosExternos(); // Cria Os Arquivos Externo;

        std::string endereco; // Caminho Onde O Projeto Ficara;
        std::string projeto; // Nome Do Projeto;
        std::string caminho_projeto;
        std::vector<std::string> pastaSrc; // Nomes Dos Arquivos Da Pasta Src;
        std::vector<std::string> pastaInclude; // Nomes Dos Arquivos Da Pasta Include;
        std::vector<std::string> PastaExterna; // Nomes Dos Arquivos Do Projeto;
    public:
        void createProject();
};


#endif