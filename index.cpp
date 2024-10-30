#include <iostream>
#include <cstdio>
#include <limits>
#include <cstring>

using namespace std;

struct emprestimos
{
    char dt_emp[10], dt_dev[10], usuario[255];
};

struct livros
{
    int codigo, paginas;
    char area[30], titulo[255], autores[255], editora[50];
    struct emprestimos emp;
};

int opcMenu, cod, pos;
char opc;

FILE *arquivo, *arquivoAux;

struct livros livro;

void limparTela()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void linha()
{
    cout << "==-=-=-=-=-=-=--=-=-=-=-=-=-=-==-=-=-=-=-=-=--=-=-=-=-=-=-=-==" << endl;
}

void listarLivros()
{
    arquivo = fopen("bd.sgb", "rb");
    if (arquivo != NULL)
    {
        limparTela();
        linha();
        fread(&livro, sizeof(struct livros), 1, arquivo);
        while (!feof(arquivo))
        {
            cout << "Codigo: " << livro.codigo << endl;
            cout << "Area: " << livro.area << endl;
            cout << "Titulo: " << livro.titulo << endl;
            cout << "Autor(es): " << livro.autores << endl;
            cout << "Editora: " << livro.editora << endl;
            cout << "N paginas: " << livro.paginas << endl;
            linha();
            fread(&livro, sizeof(struct livros), 1, arquivo);
        }
        fclose(arquivo);
        linha();
        cin.ignore();
        cin.get();
    }
    else
    {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void livrosDisponiveis()
{
    arquivo = fopen("bd.sgb", "rb");
    if (arquivo != NULL)
    {
        limparTela();
        linha();
        fread(&livro, sizeof(struct livros), 1, arquivo);
        while (!feof(arquivo))
        {
            if (strcmp(livro.emp.dt_emp, "") == 0)
            {
                cout << "Codigo: " << livro.codigo << endl;
                cout << "Area: " << livro.area << endl;
                cout << "Titulo: " << livro.titulo << endl;
                cout << "Autor(es): " << livro.autores << endl;
                cout << "Editora: " << livro.editora << endl;
                cout << "N paginas: " << livro.paginas << endl;
                linha();
            }
            fread(&livro, sizeof(struct livros), 1, arquivo);
        }
        fclose(arquivo);
        linha();
        cin.ignore();
        cin.get();
    }
    else
    {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void pesquisarLivro()
{
    arquivo = fopen("bd.sgb", "rb");
    if (arquivo != NULL)
    {
        limparTela();
        linha();
        cout << "Digite o Codigo do livro que deseja pesquisar: ";
        cin >> cod;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        int achou = 0;
        while (!feof(arquivo))
        {
            fread(&livro, sizeof(struct livros), 1, arquivo);
            if (cod == livro.codigo)
            {
                achou = 1;
                limparTela();
                linha();
                cout << "Codigo: " << livro.codigo << endl;
                cout << "Area: " << livro.area << endl;
                cout << "Titulo: " << livro.titulo << endl;
                cout << "Autor(es): " << livro.autores << endl;
                cout << "Editora: " << livro.editora << endl;
                cout << "N paginas: " << livro.paginas << endl;
                linha();
                cin.get();
                break;
            }
        }
        fclose(arquivo);

        if (!achou)
        {
            limparTela();
            linha();
            cout << "Livro nao encontrado!" << endl;
            linha();
            cin.ignore();
        }
    }
    else
    {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void devolverLivro()
{
    arquivo = fopen("bd.sgb", "rb+");
    if (arquivo != NULL)
    {
        limparTela();
        linha();
        cout << "Digite o Codigo do livro que deseja devolver: ";
        cin >> cod;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        int achou = 0;
        pos = -1;
        while (!feof(arquivo))
        {
            fread(&livro, sizeof(struct livros), 1, arquivo);
            pos++;
            if (cod == livro.codigo)
            {
                achou = 1;
                fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                strcpy(livro.emp.dt_emp, "");
                strcpy(livro.emp.dt_dev, "");
                strcpy(livro.emp.usuario, "");
                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                break;
            }
        }
        fclose(arquivo);

        limparTela();
        if (achou)
        {
            linha();
            cout << "Livro devolvido com sucesso!" << endl;
            linha();
        }
        else
        {
            linha();
            cout << "Livro nao encontrado!" << endl;
            linha();
        }
        cin.ignore();
    }
    else
    {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void emprestarLivro()
{
    arquivo = fopen("bd.sgb", "rb+");
    if (arquivo != NULL)
    {
        limparTela();
        linha();
        cout << "Digite o Codigo do livro que deseja emprestar: ";
        cin >> cod;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        pos = -1;
        int achou = 0;
        while (!feof(arquivo))
        {
            fread(&livro, sizeof(struct livros), 1, arquivo);
            pos++;
            if (cod == livro.codigo)
            {
                achou = 1;
                limparTela();
                linha();
                fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                cout << "Data de emprestimo: ";
                cin.get(livro.emp.dt_emp, 10);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                linha();
                cout << "Data de devolucao: ";
                cin.get(livro.emp.dt_dev, 10);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                linha();
                cout << "Usuario: ";
                cin.get(livro.emp.usuario, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                fwrite(&livro, sizeof(struct livros), 1, arquivo);
                break;
            }
        }
        fclose(arquivo);

        limparTela();
        if (achou)
        {
            linha();
            cout << "Livro emprestado com sucesso!" << endl;
            linha();
        }
        else
        {
            linha();
            cout << "Livro nao encontrado!" << endl;
            linha();
        }
        cin.ignore();
    }
    else
    {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void excluirLivro()
{
    limparTela();
    linha();
    cout << "Digite o Codigo do livro que deseja excluir: ";
    cin >> cod;
    limparTela();
    linha();
    arquivo = fopen("bd.sgb", "rb");
    arquivoAux = fopen("bd.aux", "wb");
    int achou = 0;
    fread(&livro, sizeof(struct livros), 1, arquivo);
    while (!feof(arquivo))
    {
        if (cod != livro.codigo)
        {
            fwrite(&livro, sizeof(struct livros), 1, arquivoAux);
        }
        if (cod == livro.codigo)
        {
            achou = 1;
        }
        fread(&livro, sizeof(struct livros), 1, arquivo);
    }

    fclose(arquivo);
    fclose(arquivoAux);
    remove("bd.sgb");
    rename("bd.aux", "bd.sgb");
    limparTela();
    linha();
    if (achou)
    {
        cout << "Livro excluido com sucesso!" << endl;
    }
    else
    {
        cout << "Livro nao encontrado!" << endl;
    }
    linha();
    cin.ignore();
    cin.get();
}

void alterarLivro()
{
    arquivo = fopen("bd.sgb", "rb+");
    if (arquivo != NULL)
    {
        limparTela();
        linha();
        cout << "Digite o Codigo do livro que deseja alterar: ";
        cin >> cod;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        int achou = 0;
        pos = -1;
        while (!feof(arquivo))
        {
            fread(&livro, sizeof(struct livros), 1, arquivo);
            pos++;
            if (cod == livro.codigo)
            {
                achou = 1;
                limparTela();
                linha();
                cout << "Area: ";
                cin.get(livro.area, 30);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                linha();
                cout << "Titulo: ";
                cin.get(livro.titulo, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                linha();
                cout << "Autor(es): ";
                cin.get(livro.autores, 255);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                linha();
                cout << "Editora: ";
                cin.get(livro.editora, 50);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                linha();
                cout << "N paginas: ";
                cin >> livro.paginas;

                fseek(arquivo, sizeof(struct livros) * pos, SEEK_SET);
                if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1)
                {
                    limparTela();
                    linha();
                    cout << "Livro alterado com sucesso!" << endl;
                    linha();
                }
                else
                {
                    limparTela();
                    linha();
                    cout << "Erro ao alterar o livro!" << endl;
                    linha();
                }
                cin.ignore();
                cin.get();
                break;
            }
        }
        fclose(arquivo);
        limparTela();
        linha();
        if (achou)
        {
            cout << "Livro alterado com sucesso!" << endl;
        }
        else
        {
            cout << "Livro nao encontrado!" << endl;
        }
        linha();
        cin.ignore();
    }
    else
    {
        cout << "Erro ao abrir o banco de dados!";
        cin.ignore();
        cin.get();
    }
}

void cadastrarLivro()
{
    limparTela();
    linha();
    cout << "Deseja cadastrar um livro (S ou N)?";
    cin >> opc;
    limparTela();
    linha();
    while (opc == 'S')
    {
        limparTela();
        linha();
        cout << "Codigo: ";
        cin >> livro.codigo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        cout << "Area: ";
        cin.get(livro.area, 30);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        cout << "Titulo: ";
        cin.get(livro.titulo, 255);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        cout << "Autor(es): ";
        cin.get(livro.autores, 255);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        cout << "Editora: ";
        cin.get(livro.editora, 50);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        linha();
        cout << "N paginas: ";
        cin >> livro.paginas;

        arquivo = fopen("bd.sgb", "ab");
        if (arquivo == NULL)
        {
            arquivo = fopen("bd.sgb", "wb");
        }

        if (fwrite(&livro, sizeof(struct livros), 1, arquivo) == 1)
        {
            limparTela();
            linha();
            cout << "Livro cadastrado com sucesso!" << endl;
            linha();
        }
        else
        {
            limparTela();
            linha();
            cout << "Erro ao cadastrar o livro!" << endl;
            linha();
        }
        fclose(arquivo);

        cin.ignore();
        cin.get();
        limparTela();
        linha();
        cout << "Deseja cadastrar um livro (S ou N)?";
        cin >> opc;
        limparTela();
    }
}

int verificaArquivo()
{
    arquivo = fopen("bd.sgb", "rb");
    if (arquivo == NULL)
    {
        arquivo = fopen("bd.sgb", "wb");
        if (arquivo == NULL)
        {
            cout << "Erro ao criar o banco de dados!";
            cin.ignore();
            cin.get();
            return 0;
        }
    }
    fclose(arquivo);
    return 1;
}

int main()
{
    if (!verificaArquivo())
    {
        return 1;
    }
    do
    {
        cout << "||=-=-=-=-=-=-=--=-=-=-=-=-=-=-=|| \n";
        cout << "::\t ____________  \t\t::\n";
        cout << "||\t|            | \t\t||\n";
        cout << "::\t| SISTEMA    | \t\t::\n";
        cout << "||\t|GERENCIADOR |\t\t||\n";
        cout << "::\t| DE         | \t\t::\n";
        cout << "::\t| BIBLIOTECA | \t\t::\n";
        cout << "||\t------||------\t\t||\n";
        cout << "::\t(\\/)  ||      \t\t::\n";
        cout << "||\t(*-*) ||      \t\t||\n";
        cout << "::\t/    }||      \t\t::\n";
        cout << "||=-=-=-=-=-=-=--=-=-=-=-=-=-=-=|| \n";
        cout << ":: 1 - Cadastro \t\t::" << endl;
        cout << "|| 2 - Alterar \t\t\t||" << endl;
        cout << ":: 3 - Excluir \t\t\t::" << endl;
        cout << "|| 4 - Emprestar \t\t||" << endl;
        cout << ":: 5 - Devolver \t\t::" << endl;
        cout << "|| 6 - Consulta de livro \t||" << endl;
        cout << ":: 7 - Livros disponiveis \t::" << endl;
        cout << "|| 8 - Listagem geral de livros ||" << endl;
        cout << ":: 9 - Sair \t\t\t::" << endl;
        cout << "||=-=-=-=-=-=-=--=-=-=-=-=-=-=-=|| \n\n";
        cout << "Digite a opcao desejada: ";
        cin >> opcMenu;

        switch (opcMenu)
        {
        case 1:
            cadastrarLivro();
            break;
        case 2:
            alterarLivro();
            break;
        case 3:
            excluirLivro();
            break;
        case 4:
            emprestarLivro();
            break;
        case 5:
            devolverLivro();
            break;
        case 6:
            pesquisarLivro();
            break;
        case 7:
            livrosDisponiveis();
            break;
        case 8:
            listarLivros();
            break;
        case 9:
            limparTela();
            linha();
            cout << "Obrigado por utilizar nosso sistema!\nAperte QUALQUER TECLA para sair...\n";
            linha();
            cin.ignore();
            cin.get();
            break;
        default:
            cout << "Informe uma opção válida!";
            break;
        }
        limparTela();
    } while (opcMenu != 9);
}