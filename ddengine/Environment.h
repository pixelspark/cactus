/** PORTING STATUS: Still uncompleted, uncomment the line "Texture background;" when class Texture
is finished. **/

#ifndef __DDENGINE_ENVIRONMENT_H
#define __DDENGINE_ENVIRONMENT_H

class Environment {
public:
	Environment();
	virtual ~Environment();
	int ambient;
	int fogcolor;
	int fogfact;
	int bgcolor;
	///Texture background;
};

#endif
