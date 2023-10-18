#ifndef _COMMUNICATOR_UI_H_
#define _COMMUNICATOR_UI_H_

#include <UserInterface.h>
#include <Communicator.h>

class CommunicatorUI: public UserInterface {
public:
    CommunicatorUI(Communicator* com);

    void show();
    void readUserIntput();

private:
    Communicator* com;
};

#endif  // _COMMUNICATOR_UI_H_