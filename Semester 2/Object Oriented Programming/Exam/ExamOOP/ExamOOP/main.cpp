#include <iostream>
#include <QApplication>
#include "RepoStars.h"
#include "RepoAstronomer.h"
#include "AstronomerWindow.h"

int main(int argc, char** argv) {
    QApplication a(argc, argv);

    RepoStars repoStars;
    RepoAstronomer repoAstronomer;
    std::vector<AstronomerWindow*> windows;
    for (auto& a : repoAstronomer.getAstronomers()) {
        windows.push_back(new AstronomerWindow(repoStars, a));
    }

    return a.exec();
}