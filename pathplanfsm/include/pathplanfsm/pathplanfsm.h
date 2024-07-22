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
            


}   ;
// #endif