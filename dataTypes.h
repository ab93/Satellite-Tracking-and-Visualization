#ifndef DATATYPES_H
#define DATATYPES_H

#include <string>
#include <QString>
using namespace std;

typedef struct	{
                   double  epoch, xndt2o, xndd6o, bstar, xincl,
                           xnodeo, eo, omegao, xmo, xno;
                   int	   catnr, elset, revnum;
                   char	   sat_name[25], idesg[9];
                }  tle_t;

/* Geodetic position structure used by SGP4/SDP4 code (LATITUDE, LONGITUDE & ALTITUDE). */

typedef struct	{
                   double lat, lon, alt, theta;
                }  geodetic_t;

/* General three-dimensional vector structure used by SGP4/SDP4 code (3D VECTOR). */

typedef struct	{
                   double x, y, z, w;
                }  vector_t;

/* Common arguments between deep-space functions used by SGP4/SDP4 code. */

typedef struct	{
                           /* Used by dpinit part of Deep() */
                   double  eosq, sinio, cosio, betao, aodp, theta2,
                           sing, cosg, betao2, xmdot, omgdot, xnodot, xnodp;

                           /* Used by dpsec and dpper parts of Deep() */
                   double  xll, omgadf, xnode, em, xinc, xn, t;

                           /* Used by thetg and Deep() */
                   double  ds50;
                }  deep_arg_t;



struct SatelliteParam
{
    //string name;
    QString name;
    vector_t coord;
    double velocity;
    int count;
    double footprint;
    double altitude;
    float latitude;
    float longitude;
    QString date;
};

struct satellite_info
{          char line1[70];
           char line2[70];
           char name[25];
           long catnum;
           long setnum;
           char designator[10];
           int year;
           double refepoch;
           double incl;
           double raan;
           double eccn;
           double argper;
           double meanan;
           double meanmo;
           double drag;
           double nddot6;
           double bstar;
           long orbitnum;
        }  ;//sat[24];

struct	qth_info
{          char callsign[17];
           double stnlat;
           double stnlong;
           int stnalt;
        };//  qth;

struct	satellite_db
{          char name[25];
           long catnum;
           char squintflag;
           double alat;
           double alon;
           unsigned char transponders;
           char transponder_name[10][80];
           double uplink_start[10];
           double uplink_end[10];
           double downlink_start[10];
           double downlink_end[10];
           unsigned char dayofweek[10];
           int phase_start[10];
           int phase_end[10];
        };//  sat_db[24];


#endif // DATATYPES_H
