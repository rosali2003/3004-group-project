#ifndef SESSION_H
#define SESSION_H


class Session
{
public:
    Session();
    bool beginSession();
    bool quitSession();
private:
    bool sessionRunning;
};

#endif // SESSION_H
