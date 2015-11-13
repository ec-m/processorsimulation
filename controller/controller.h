#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QObject>
#include <QFileInfo>
#include "model/message.h"

/*
 * The class Controller receives messages from the GUI
 * and checks their content (for example a new value, the
 * user inserted in a RAM cell). If everything is correct,
 * the Controller forwards the message to the Model. If
 * not, it notifies the GUI, that something went wrong
 * (for example, that the user inserted something forbidden).
 * @author: Eva Charlotte Mayer
 */

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);

signals:
    void sendMessage(Message &msg);

public slots:
    void notify(Message &msg);

private:
    // Checks if file exists and if so, sends filename to Model
    void checkFileOpen(Message &msg);

    // Checks if new PC value is in defined range and valid input for current mode
    void checkUserInputPC(Message &msg);

    // Checks if new OpCode value is in defined range and valid input for current mode
    void checkUserInputOpCode(Message &msg);

    // Checks if new Address value is in defined range and valid input for current mode
    void checkUserInputAddress(Message &msg);

    // Checks if new Accu value is in defined range and valid input for current mode
    void checkUserInputAccu(Message &msg);

    // Checks if new RAM value is in defined range and valid input for current mode
    void checkUserInputRAM(Message &msg);

    // Converts the new value into a ushort so it can be sent to Model
    ushort convertMsgContent(Message &msg);

    // Converts a MnemonicString "OPCODE <Address>" to a ushort so it can be send to Model
    ushort convertToMnemonic_UserInputRAM(QString s);

    // Converts a MnemonicString "OPCODE" to a ushort so it can be send to Model
    ushort convertToMnemonic_UserInputOpCode(QString s);

    // Attribute
    // Used to check if conversions worked (true if conversion succeeded, false if it failes)
    bool ok;
};

#endif // CONTROLLER_H
