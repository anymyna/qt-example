/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "videoplayer.h"

#include <QtWidgets/QApplication>
#include <QtWidgets/QDesktopWidget>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QtCore/QDir>
#include <QDebug>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Video Widget Example");
    QCoreApplication::setOrganizationName("QtProject");
    QGuiApplication::setApplicationDisplayName(QCoreApplication::applicationName());
    QCoreApplication::setApplicationVersion(QT_VERSION_STR);
    QCommandLineParser parser;
    parser.setApplicationDescription("Qt Video Widget Example");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The URL to open.");
    parser.process(app);

    VideoPlayer player;
    if (!parser.positionalArguments().isEmpty()) {
        const QUrl url =
            QUrl::fromUserInput(parser.positionalArguments().constFirst(),
                                QDir::currentPath(), QUrl::AssumeLocalFile);
        player.setUrl(url);
    }

    const QRect availableGeometry = QApplication::desktop()->availableGeometry(&player);
    //player.resize(availableGeometry.width() / 6, availableGeometry.height() / 4);


    player.setWindowFlags(player.windowFlags()&~Qt::WindowMaximizeButtonHint);// 禁止最大化按钮
    player.show();
    qDebug()<<"main currentPath"<< QDir::currentPath()<<endl;

     //Qt写ini文件
     QSettings *configIniWrite = new QSettings("hahaya.ini", QSettings::IniFormat);
     //向ini文件中写入内容,setValue函数的两个参数是键值对
     //向ini文件的第一个节写入内容,ip节下的第一个参数
     configIniWrite->setValue("/ip/first", "192.168.0.1");
     //向ini文件的第一个节写入内容,ip节下的第二个参数
     configIniWrite->setValue("ip/second", "127.0.0.1");
     //向ini文件的第二个节写入内容,port节下的第一个参数
     configIniWrite->setValue("port/open", "2222");
     //写入完成后删除指针
     delete configIniWrite;

     QSettings *configIniRead = new QSettings("hahaya.ini", QSettings::IniFormat);
     //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型
     QString ipResult = configIniRead->value("/ip/second").toString();
     QString portResult = configIniRead->value("/port/open").toString();
     //打印得到的结果
     qDebug() << ipResult;
     qDebug() << portResult;
     //读入入完成后删除指针
     delete configIniRead;


    return app.exec();
}
