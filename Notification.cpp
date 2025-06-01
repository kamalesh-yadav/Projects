#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
using namespace std;

/*================================
    Notification and decorators
  ================================*/

  class INotification
  {
    public:
    virtual string getContent() const=0;
    virtual ~INotification(){}
  };
  // concrete notification: simple text notification
  class SimpleNotification:public INotification
  {
    private:
    string text;
    public:
    SimpleNotification(const string& msg)
    {
        text=msg;
    }
    string getContent() const override
    {
        return text;
    }
  };
// Abstract decorator: wraps a notification object
class INotificationDecorator:public INotification // is a relationship
{
    protected:
    INotification* notification; // has a relationship
    public:
    INotificationDecorator(INotification* n)
    {
        notification=n;
    }
    virtual ~INotificationDecorator()
    {
        delete notification;
    }
};
// Decorator to add a timestamp to content
class TimestampDecorator:public INotificationDecorator
{
    public:
    TimestampDecorator(INotification*n):INotificationDecorator(n){}
    string getContent() const override
    {
        return "[30-05-2025 15:46:00]" + notification->getContent();
    }
};
// Decorator to add a signature to content
class SignatureDecorator:public INotificationDecorator
{
    private:
    string signature;
    public:
    SignatureDecorator(INotification*n,const string& sig):INotificationDecorator(n)
    {
        signature = sig;
    }
    string getContent() const override
    {
        return notification->getContent() + "\n--"+signature+"\n\n";
    }
};

/*====================================
      Observer Pattern Components
  ====================================*/

  //Observer Interface:each observer gets an update with a notification pointer
class IObserver
{
    public:
    virtual void update()=0;
    virtual ~IObserver(){}
};

class IObservable
{
    public:
    virtual void addObserver(IObserver* observer)=0;
    virtual void removeObserver(IObserver* observer)=0;
    virtual void notifyObservers()=0;
};
// concrete Observable
class NotificationObservable:public IObservable
{
    private:
    vector<IObserver*>observers;
    INotification* currentNotification;
    public:
    NotificationObservable()
    {
        currentNotification=NULL;
    }
    void addObserver(IObserver* obs) override
    {
        observers.push_back(obs);
    }
    void removeObserver(IObserver* obs) override
    {
        observers.erase(remove(observers.begin(),observers.end(),obs),observers.end());
    }
    void notifyObservers() override
    {
        for(unsigned int i = 0; i<observers.size(); ++i)
        {
            observers[i]->update();
        }
    }
    void setNotification(INotification* notification)
    {
        if(currentNotification!=NULL)
        {
            delete currentNotification;
        }
        currentNotification=notification;
        notifyObservers();
    }
    INotification* getNotification()
    {
        return currentNotification;
    }
    string getNotificationContent()
    {
        return currentNotification->getContent();
    }
    ~NotificationObservable()
    {
        if(currentNotification!=NULL)
        {
            delete currentNotification;
        }
    }
};
// Concrete Observer 1
class Logger:public IObserver
{
    private:
    NotificationObservable* notificationObservable;
    public:
    Logger(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

     void update() {
        cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
    }
   
};

/*=============================================
    Strategy Pattern Components(Observer 2)
===============================================*/

/*Abstract class for different stratagies*/
class INotificationStratagies
{
    public:
    virtual void sendNotification(string content)=0;
};

class EmailStrategy:public INotificationStratagies
{
    private:
    string Emailid;
    public:
    EmailStrategy(string Emailid)
    {
        this->Emailid=Emailid;
    }
    void sendNotification(string content) override
    {
        /*Simulate the process of sending an email notification*/
        /*Representing the dispatch of message to user via email.*/
        cout<<"Sending Email Notification to:"<<Emailid<<endl<<content;
    }
};
class SMSStrategy:public INotificationStratagies
{
    private:
    string mobileNumber;
    public:
    SMSStrategy(string mobileNumber)
    {
        this->mobileNumber=mobileNumber;
    }
    void sendNotification(string content) override
    {
        /*Simulate the process of sending an email notification*/
        /*Representing the dispatch of message to user via SMS.*/
        cout<<"Sending Email Notification to:"<<mobileNumber<<endl<<content;
    }
};
class PopUpStrategy:public INotificationStratagies
{
    public:
    void sendNotification(string content) override
    {
        /*Simulate the process of sending pop-up Notification*/
        cout<<"Sending Pop-Up Notification:"<<endl<<content;
    }
};

class NotificationEngine:public IObserver
{
    private:
    NotificationObservable* notificationObservable;
    vector<INotificationStratagies*>notificationstratagies;
    public:
    NotificationEngine(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

    void addNotificationStrategy(INotificationStratagies* ns) {
        this->notificationstratagies.push_back(ns);
    }

    // Can have RemoveNotificationStrategy as well.

    void update() {
        string notificationContent = notificationObservable->getNotificationContent();
        for(const auto notificationStratagies : notificationstratagies) {
            notificationStratagies->sendNotification(notificationContent);
        }
    }
  
};

/*=======================================
         Notification Servive
=========================================*/
/*The Notification Service manages notification.It keeps track of notification*/
/*Any client code will interact with this service*/

/*Singelton class*/
class NotificationService
{
    private:
    NotificationObservable* observable;
    static NotificationService* instance;
    vector<INotification*> notifications;
    NotificationService()
    {
        /*Private constructor*/
        observable= new NotificationObservable();
    }
    public:
    static NotificationService* getInstance()
    {
        if(instance==NULL)
        {
            instance = new NotificationService();
        }
        return instance;
    }
    /*Expose the observable so observers can watch*/
    NotificationObservable* getObservable()
    {
        return observable;
    }
    /*Create A New Notification and notifies Observers*/
    void sendNotification(INotification* notification)
    {
        notifications.push_back(notification);
        observable->setNotification(notification);
    }
    ~NotificationService()
    {
        delete observable;
    }
};
NotificationService*NotificationService::instance=NULL;
/*Main Function*/
int main()
{
    /*Create Notification Service*/
    NotificationService* notificationService = NotificationService::getInstance();
    /*Get Observable*/
    NotificationObservable* notificationObservable = notificationService->getObservable();
    /*Create Logger */
    Logger* logger = new Logger(notificationObservable);
    /*Create Notification Engine Observers*/
    NotificationEngine* notificationEngine = new NotificationEngine(notificationObservable);

    notificationEngine->addNotificationStrategy(new EmailStrategy("kamleshysy123@gmail.com"));
    notificationEngine->addNotificationStrategy(new SMSStrategy("+91 9125957212"));
    notificationEngine->addNotificationStrategy(new PopUpStrategy());

    /*Attach these observers*/
    notificationObservable->addObserver(logger);
    notificationObservable->addObserver(notificationEngine);

    /*Create a Notification with decorators*/
    INotification* notification = new SimpleNotification("Your Orders has been shipped!");
    notification = new TimestampDecorator(notification);
    notification= new SignatureDecorator(notification,"Customar Care");
    notificationService->sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}