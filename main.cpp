/*!
*   \mainpage Introduction
*
*   \brief Tesis de la carrera Licenciatura en Ciencias de la Computacón de la
*   <a href="http://www.unrc.edu.ar/">Universidad Nacional de Ro Cuarto </a> -
*   <a href="http://dc.exa.unrc.edu.ar"> Facultad de Ciencias Exactas Fsico Qumicas, Departameto de Computación </a>
*
*   \section intro Herramienta para la creación de aplicaciones NCL para el middleware GINGA de Televisión Digital Terrestre
*
*   La Televisión Digital Terrestre (<a href="http://www.tvdigitalargentina.gov.ar/tvdigital">TDT</a>) es una nueva técnica
*   de difusión de las señales de televisión que promete sustituir a la televisión analógica actual.
*
*   Al recibir señal digital, es necesario tener un decodificador (Set-Top Box) que sea capaz de interpretar la señal y
*   ejecutar aplicaciones <a href="http://www.ginga.org.br"> Ginga </a>.
*
*   Ginga es el nombre de la plataforma de ejecución de software para la televisión desarrollada por universidades Brasileras
*   y con importantes aportes desarrollados por el LIFIA de la Universidad Nacional de La Plata. Gracias a este middleware
*   además de generar contenidos para televisión, podemos ejecutar las aplicaciones que acompañen a cada programa/película en
*   un Set-Top Box (STB). La señal de TVD es enviada desde una central emisora a retransmisoras ubicadas en distintos
*   lugares para así llegar a cada TV por medio del modelo de broadcasting.
*
*   En la señal, además del video y audio, son enviados también los datos (que representan aplicaciones) de tal forma que el
*   Set-Top Box pueda procesarlos para mostrar la información en la TV.
*
*   Ginga soporta los paradigmas de programación declarativo e imperativo. El lenguaje declarativo admitido por Ginga es NCL
*   (Nested Context Languaje) y el imperativo es el lenguaje llamado Lua. Una de las grandes ventajas de Ginga es que
*   es el único estándar internacional y también abierto.
*
*   El lenguaje declarativo NCL basado en el modelo conceptual NCM (Nested Context Model) provee facilidades para
*   especificar aspectos de interactividad, sincronismo espacial/temporal entre objetos de multimedia, adaptabilidad y soporte
*   para múltiples dispositivos (TV, PC, Dispositivos Móviles).
*
*   Si bien NCL no es un lenguaje complicado de aprender para personas en el ámbito de la programación, sería importante poder
*   realizar aplicaciones para TVD sin la obligación de poseer conocimientos de programación, por lo que se realizó una
*   herramienta de alto nivel con la cual se puede crear aplicaciones por medio de la interacción del usuario sin la necesidad
*   de escribir código NCL.
*
*   <b> “CreaTV Digital” es una herramienta de fácil manejo destinada a desarrolladores de contenidos con una interface orientada a
*   la producción de contenidos interactivos de Televisión Digital de manera gráfica, sin la necesidad de conocimientos
*   detallados de los lenguajes NCL y Lua. La herramienta permite al usuario, por medio de una interfaz gráfica e intuitiva,
*   realizar el contenido (programa/película junto con su aplicación interactiva) que será emitido y luego ésta se encargará de
*   crear el código NCL correspondiente para poder ser ejecutado en el middleware Ginga. </b>
*
*   Desarrolado en el lenguaje C++ con la <a href="http://qt.nokia.com/">Biblioteca Multiplataforma Qt</a>.
*
*   \author Cardozo, Sergio A.
*   \author Schwartz, Sebastian M.
*   \version 1.0
*   \date 2011
*/


#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QString translatorFileName = QLatin1String("qt_");
    QTranslator *translator = new QTranslator(&a);
    translatorFileName += QLocale::system().name();

    if (translator->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(translator);
    MainWindow w;
    w.show();
    return a.exec();
}
