// #ifdef _PATHPLANFSM_H
// #define _PATHPLANFSM_H

#include <ros/ros.h>
#include <Eigen/Core>
#include <geometry_msgs/PointStamped.h>
#include <math.h>
#include <vector>

using namespace std;
using namespace Eigen;
using namespace geometry_msgs;
class PathPlanFSMItem {
    friend class PathPlanFSM ;
    public:
    enum State{
        IDLE = 0,
        STakeOff,
        SFly,
        SReturn,
        Sland
    };

    
    private:
    
    virtual PointStamped PTakeOff(double  time, Vector3d TakeOffPoint) = 0;

    virtual PointStamped PtoP (double  time, double vel) = 0;

    virtual PointStamped Land (double time, Vector3d LandPoint) = 0;
    
    public:
    enum Events {
        ETakeOff = 0,
        EReachPoint ,
        ETaskFinish ,
        EReturn ,
        Eland ,
    };
    
    private:
    State _curState;
    Events _event;
    PointStamped (*_action)();
    State _nextState;
    
    public:
    PathPlanFSMItem(State curState, PointStamped (*action)(), State nextState, Events event):
    _curState(curState), _nextState(nextState), _action(action), _event(event){};
    
}   ;

class PathPlanFSM {
     private : vector<PathPlanFSMItem> _fsmTable;
     
     public :
     void initFSMTable (){

     }
     public:
        PathPlanFSMItem::State _curState;

     public :
     PathPlanFSM (PathPlanFSMItem::State curState = PathPlanFSMItem::IDLE):_curState(curState){
        initFSMTable();
     } 
     void transferState(PathPlanFSMItem::State nextState){
        _curState = nextState;   
        //将传入的 nextState 赋值给_fsm 的现态 _curState
    }
};
// #endif