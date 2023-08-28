#include "./include/criadorprojetocpp.hpp"

bool CriadorProjetoCpp::verificaCarregar(){
    bool result = false;
    if(endereco.size() != 0){
        result = true;
    }else if(projeto.size() != 0){
        result = true;
    }else if(pastaSrc.size() != 0){
        result = true;
    }else if(pastaInclude.size() != 0){
        result = true;
    }else if(PastaExterna.size() != 0){
        result = true;
    }
    
    return result;
}

bool CriadorProjetoCpp::carregar(){
    bool result = false;
    const std::string arquivo{"projeto.config"};
    std::fstream config{arquivo};
    std::string linha;
    try{
        if(config.is_open()){
            do{
                if(linha.find("url") == 0){
                    std::string _url = linha.substr(4);
                    if(!_url.empty()){
                        endereco = _url;
                    }

                }else if(linha.find("project") == 0){
                    std::string _nome = linha.substr(8);
                    if(!_nome.empty()){
                        projeto = _nome;
                    } 
                }else if(linha.find("src") == 0){
                    std::string _src = linha.substr(4);
                    if(!_src.empty()){
                        pastaSrc.push_back(_src);
                    }
                }else if(linha.find("include") == 0){
                    std::string _include = linha.substr(8);
                    if(!_include.empty()){
                        pastaInclude.push_back(_include);
                    }
                }else if(linha.find("extern") == 0){
                    std::string _extern = linha.substr(7);
                    if(!_extern.empty()){
                        PastaExterna.push_back(_extern);
                    }
                }

            }while(std::getline(config, linha));
            
            caminho_projeto = endereco + "/" + projeto;
            if(verificaCarregar()){
                result = true;
            }
            return result;
        }
    }catch(const std::exception& e){
        std::cerr << "Um Erro Ocorreu ao Criar O Projeto: " << e.what()  << '\n';
    }
    config.close();
    return result;
}

bool CriadorProjetoCpp::criarPastaProjeto(){
    bool result = false;
    #ifndef _WIN32
        if(_mkdir(caminho_projeto.c_str()) == 0){
    #else
        if(mkdir(caminho_projeto.c_str()) == 0){
    #endif 
        result = true;
    }

    return result;
}

bool CriadorProjetoCpp::criarPastaSrc(){
    bool result = false;
    const std::string src = caminho_projeto + "/src";

    #ifndef _WIN32
        if(_mkdir(src.c_str()) == 0){
    #else
        if(mkdir(src.c_str()) == 0){
    #endif 
        result = true;
    }else{
        std::cerr << "Info: Nao Foi Possivel Criar A Pasta src" << '\n';
    }

    return result;

}

bool CriadorProjetoCpp::criarArquivosSrc(){
    bool result = false;
    const std::string src = caminho_projeto + "/src/";
    for(std::string arquivo: pastaSrc){
        if(arquivo != "vazio"){
            std::ofstream create((src + arquivo));
            if(create.is_open()){
                create.close();
                std::cout << "Info: Arquivo: " << arquivo << " Criado Com Sucesso" << '\n';
                 result = true;


            }else if(arquivo == "vazio"){     
                result = true;
            }else{
                std::cerr << "Arquivo: " << arquivo << " Erro Ao Criar O Arquivo" << '\n';
            }

        }
    }
   
    
    return result;

}

bool CriadorProjetoCpp::criarPastaInclude(){
    bool result = false;
    const std::string include = caminho_projeto + "/src/include";
    #ifndef _WIN32
        if(_mkdir(include.c_str()) == 0){
    #else
        if(mkdir(include.c_str()) == 0){
    #endif 
        result = true;
    }else{
        std::cerr << "Info: Nao Foi Possivel Criar A Pasta include" << '\n';
    }

    return result;



}

bool CriadorProjetoCpp::criarArquivosInclude(){
    bool result = false;
    const std::string include = caminho_projeto + "/src/include/";

    for(std::string arquivo: pastaInclude){
        if(arquivo != "vazio"){
            std::fstream arq(include + arquivo);
            if(arq.is_open()){
                arq.close();
                std::cout << "Info: Arquivo: " << arquivo << " Criado Com Sucesso" << '\n';
                result = true;
            }
        }else if(arquivo == "vazio"){
            result = true;
        }
    }
    return result;

}

bool CriadorProjetoCpp::criarArquivosExternos(){
    bool result = false;
    std::string caminho = caminho_projeto + "/";
    std::replace(caminho.begin(), caminho.end(), '\\', '/');
    for(std::string arquivos: PastaExterna){
        if(arquivos != "vazio"){
            std::ofstream arquivo(caminho + arquivos);
            if(arquivo.is_open()){

                if(arquivos == "CMakeLists.txt"){
                    arquivo << "cmake_minimum_required(VERSION 3.27)" << std::endl;
                    arquivo << "project(" << projeto << ")" << std::endl;                 
                    arquivo << "include_directories(${CMAKE_SOURCE_DIR}/src/include)" << std::endl;
                    arquivo << "set(SOURCE " << std::endl;
                    arquivo << "    src/main.cpp //Exemplo Para Colocar Aqui" << std::endl;
                    arquivo << ")" << std::endl;
                    arquivo << "add_executable(${PROJECT_NAME} ${SOURCE})" << std::endl;
                    arquivo << "set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)" << std::endl;
                    }

                arquivo.close();
                std::cout << "Info: Arquivo: " << arquivos << " Criado Com Sucesso" << '\n';
                result = true;
            }
        }else if(arquivos == "vazio"){
            result = true;
        }

    }
    return result;
}

void CriadorProjetoCpp::createProject(){
    if(carregar()){
        std::cout << "Info: Informacoes Carregadas" << '\n';
        if(criarPastaProjeto()){
            std::cout << "Info: Pasta Do Projeto: " << projeto << " Criado Com Sucesso" << '\n';
            if(criarPastaSrc()){
                std::cout << "Info: Pasta src Criada Com Sucesso" << '\n';
                if(criarArquivosSrc()){
                    std::cout << "Info: Arquivos Da Pasta src Criado com Sucesso" << '\n';
                    if(criarPastaInclude()){
                        std::cout << "Info: Pasta include Criada Com Sucesso" << '\n';
                        if(criarArquivosInclude()){
                            std::cout << "Info: Arquivos Da Pasta include Criado com Sucesso" << '\n';
                            if(criarArquivosExternos()){
                                std::cout << "Info: Arquivos Da Pasta Do Projeto: " << projeto << " Criado Com Sucesso" << '\n';

                                std::cout << "Info: Projeto: " << projeto << " Criado Com Sucesso" << '\n';
                            }
                        }

                    }
                }
            }
            

        }

    }
}