#ifndef COLOR_H
#define COLOR_H

class ColorRGB{
	public:
		double r, g, b;

		ColorRGB(){
			this->r=1;
			this->g=1;
			this->b=1;
		}
		ColorRGB(double r, double g, double b):r(r), g(g), b(b){};

		void set(double r, double g, double b);
};

#endif