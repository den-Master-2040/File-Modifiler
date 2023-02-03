#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <fstream>
#include <iostream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
using std::filesystem::current_path;
vector<string> path_to_files;
vector<string> fileName;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void ParseFile();
bool file_extension(string file_Extension, string namefile);
void MainWindow::SearchFile(std::string directore_path)
{
    path_to_files.clear();
    fileName.clear();
    ui->textBrowser->clear();

    if(ui->lineEdit->text().toStdString() != "")
    {
        for (const auto & entry : fs::directory_iterator(directore_path))
        {
            filesystem::path directoryPath = entry.path();
            if(file_extension(ui->lineEdit->text().toStdString(),{directoryPath.string()}))
            path_to_files.push_back({directoryPath.string()});
        }

        for(auto s : path_to_files)
        {
            ui->textBrowser->append(QString::fromStdString(s));

        }
        ParseFile();
    }
    else;   //сказать пользователю что он не ввёл расширение файла
}

bool file_extension(string file_Extension, string namefile)
{
    if(file_Extension[1] != '*')
    {
        std::reverse(file_Extension.begin(),file_Extension.end());
        std::reverse(namefile.begin(),namefile.end());

        for(size_t i = 0; i < file_Extension.size(); i++)
        {
            if(file_Extension[i] != namefile[i])
                return false;
        }
    }
    return true;
}

void XORFile(string filePath, string outFilePath,string fileName_local, int code)
{
    std::ifstream in(filePath,std::ios_base::in|std::ios_base::binary);
    std::ofstream out(outFilePath + "/"+ fileName_local,std::ios_base::out|std::ios_base::binary);
    while(in.peek()!=EOF)
        out.put(in.get()^code);
    std::ofstream test(outFilePath + "123",std::ios_base::out|std::ios_base::binary);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    SearchFile(ui->lineEdit_2->text().toStdString());
}


void MainWindow::on_pushButton_2_clicked()
{
    for(size_t i = 0; i < path_to_files.size(); i++)
        XORFile(path_to_files[i], ui->lineEdit_3->text().toStdString(),fileName[i],ui->lineEdit_4->text().toInt());
}

void ParseFile()
{
    for(auto filePath : path_to_files)
    {
        string localNameFile;

        std::reverse(filePath.begin(),filePath.end());

        for(size_t i = 0; i < filePath.size() ; i++)
        {
            if (filePath[i] != (char)92 && filePath[i] != '/' )
            localNameFile.push_back(filePath[i]);
            else break;

        }

        std::reverse(localNameFile.begin(),localNameFile.end());

        fileName.push_back(localNameFile);

    }

}

void MainWindow::on_pushButton_3_clicked()
{

    ui->textBrowser->append(QString::fromStdString(fileName[0]));
    ui->textBrowser->append(QString::fromStdString(fileName[1]));

}

