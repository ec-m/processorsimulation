#ifndef PARSER_H
#define PARSER_H
#define OPCODESLENGTH 4096
#include <QDebug>
#include <QString>
#include <QFile>
#include <QObject>
#include "model/preparser.h"
#include "model/row.h"
#include "model/toyexception.h"
#include "model/variable.h"
#include "model/pseudoccompiler.h"
#include "model/message.h"


/*
 * The class "Parser" controls the whole parsing process:
 *
 * It opens a file and reads all lines into the list "lines".
 * It then passes this list to the preparser and receives
 * the checked and formatted version of the "lines" back.
 * For each of these lines "Row"-Objects are constructed and
 * stored in list "rows". Finally, those objects are saved
 * as shorts in the array "opCodes", which is used by the RAM.
 *
 * To be able to show the content of the RAM in binary, hexa-
 * decimal as well as mnemonic format, different modes are
 * defined and the method shows the content in the given mode.
 *
 * @author: Eva Charlotte Mayer
 */

class Parser : public QObject
{
    Q_OBJECT

public slots:

signals:
    void sendMessage(Message &msg);

public:
    // Constructor
    Parser();

    // Getter
    short* getOpCodes();
    int getOpCodesLength();

    // Method to control parsing process and pass
    // file input to different types of parsers
    void controlParsing(QString filename);

    enum MODE {
        binary,
        hexadecimal,
        mnemonic,
        ram
    };
    // Method to show rows in different modes
    void showRows(const MODE &m);

    // Method to copy valid opCode-Array into "opCodesCopy"
    void copyOpCodes();

private:
    // Attributes
    short* opCodes;
    short* opCodesCopy;
    QStringList lines;
    QList<Row *> rows;
    Preparser* preparser;
    PseudoCCompiler* pseudoCCompiler;

    // Reads user file input
    void readFromFile(QString filename);

    // Parses the lines as "Row"-Objects and
    // stores these objects in the list "rows".
    QList<Row *> parse();

    // Stores Row-Objects as shorts in array
    void store();

    // Empties all lines in Parser + Preparser
    // and sets all OpCode-Array entries to zero
    void clearAll();
};

#endif // PARSER_H
