#include "img.hpp"

using namespace std;


/* Variables */
#define SIZE 1000	/* Size of png (square) */
#define BORDER 20	/* Size of space on each side - border of the png */
#define OBJSIZE 5	/* Size of walker and target */

double l = BORDER;		/* left */
double r = BORDER + SIZE;	/* right */
double t = BORDER;		/* top */
double b = BORDER + SIZE;	/* bot */
double o = BORDER + SIZE / 2;	/* origin */

gdImagePtr img;		/* Image */
FILE *pngout;		/* Output file */

/* Brushes */
gdImagePtr brushblue, brushred, brushgreen, brushblack, brushmagenta;


/* Functions */
/* Sets png up: border, startpositions, detection circle. */
void initPNG(string file)
{
	img = gdImageCreateTrueColor(SIZE + 2 * BORDER, SIZE + 2 * BORDER);
	pngout = fopen(file.c_str(), "wb");

	double scale = (SIZE * 1.0) / svar.L;
	int white, bblack, bred, bgreen, bblue, bmagenta;
	position w, ta;	/* Positions on image. */

	w.x = o + walker.pos.x * scale;
	w.y = o - walker.pos.y * scale;
	ta.x = o + svar.tarPos.x * scale;
	ta.y = o - svar.tarPos.y * scale;

	brushblue = gdImageCreate(OBJSIZE, OBJSIZE);	/* Walker */
	brushmagenta = gdImageCreate(OBJSIZE, OBJSIZE);	/* Startposition */
	brushred = gdImageCreate(OBJSIZE, OBJSIZE);	/* Target */
	brushgreen = gdImageCreate(1, 1);		/* Trajectory */
	brushblack = gdImageCreate(1, 1);		/* Border */

	gdImageColorAllocate(brushblue, 0, 0, 255);
	gdImageColorAllocate(brushmagenta, 255, 0, 255);
	gdImageColorAllocate(brushred, 255, 0, 0);
	gdImageColorAllocate(brushgreen, 34, 139, 34);
	gdImageColorAllocate(brushblack, 0, 0, 0);

	white = gdImageColorAllocate(img, 255, 255, 255);

	gdImageFill(img, 0, 0, white);

	/* Borders and detection circle */
	gdImageSetBrush(img, brushblack);
	gdImageLine(img, l, t, r, t, gdBrushed);
	gdImageLine(img, l, b, r, b, gdBrushed);
	gdImageLine(img, l, t, l, b, gdBrushed);
	gdImageLine(img, r, t, r, b, gdBrushed);
	for (int i = 1; i <= 9; i++) {
		gdImageLine(img, l, t + i * SIZE / 10, /*l + 10*/r, t + i * SIZE / 10, gdBrushed);
		gdImageLine(img, l + i * SIZE / 10, t, l + i * SIZE / 10, b, gdBrushed);
	}
	/* Doesn't work on durga */
	// double radius = svar.detecR * scale;
	// gdImageEllipse(img, ta.x, ta.y, 2 * radius, 2 * radius, gdBrushed);
	// gdImageEllipse(img, ta.x, ta.y, 4 * radius, 4 * radius, gdBrushed);
	/* Doesn't work on durga */

	/* Target position */
	gdImageSetBrush(img, brushred);
	gdImageLine(img, ta.x, ta.y, ta.x, ta.y, gdBrushed);

	/* Walker position */
	gdImageSetBrush(img, brushmagenta);
	gdImageLine(img, w.x, w.y, w.x, w.y, gdBrushed);
}

/*
 * Returns true if old and new position are further apart than the stepsize,
 * which means the position got corrected and therefore the drawing of the
 * trajectory needs to be adjusted.
 */
bool adjust(position oldp, position newp)
{
	double dx, dy;
	double epsilon = 1e-6;
	dx = newp.x - oldp.x;
	dy = newp.y - oldp.y;
	dx *= dx;
	dy *= dy;
	if (dx + dy > walker.stepL * walker.stepL + epsilon)
		return true;
	else
		return false;
}

/* Returns the out of boundary position that would have been reached. */
position getOutPos(position oldp, position newp)
{
	position ret;
	if (oldp.x - walker.stepL > newp.x)
		ret.x = newp.x + svar.L;
	else if (oldp.x + walker.stepL < newp.x)
		ret.x = newp.x - svar.L;
	else
		ret.x = newp.x;

	if (oldp.y - walker.stepL > newp.y)
		ret.y = newp.y + svar.L;
	else if (oldp.y + walker.stepL < newp.y)
		ret.y = newp.y - svar.L;
	else
		ret.y = newp.y;

	return ret;
}

/* Returns intermediate position on border. */
position getInterPos(position oldp, position &outp)
{
	double tx, ty;
	position dir, ret;
	dir.x = outp.x - oldp.x;
	dir.y = outp.y - oldp.y;

	if (dir.x > 0)
		tx = (0.5 * svar.L - oldp.x) / dir.x;
	else if (dir.x < 0)
		tx = (-0.5 * svar.L - oldp.x) / dir.x;
	else
		tx = 1e6;

	if (dir.y > 0)
		ty = (0.5 * svar.L - oldp.y) / dir.y;
	else if (dir.y < 0)
		ty = (-0.5 * svar.L - oldp.y) / dir.y;
	else
		ty = 1e6;

	if (tx <= ty) {
		ret.x = oldp.x + tx * dir.x;
		ret.y = oldp.y + tx * dir.y;
	} else {
		ret.x = oldp.x + ty * dir.x;
		ret.y = oldp.y + ty * dir.y;
	}

	return ret;
}

/* Returns position on opposite side of the border */
position getOppPos(position pos)
{
	if (pos.x >= 0.5 * svar.L)
		pos.x -= svar.L;
	else if (pos.x <= -0.5 * svar.L)
		pos.x += svar.L;
	if (pos.y >= 0.5 * svar.L)
		pos.y -= svar.L;
	else if (pos.y <= -0.5 * svar.L)
		pos.y += svar.L;

	return pos;
}
/* Updates image with walker trajectory incl. border crossing steps. */
void pbc_updatePNG(position oldp, position newp)
{
	double scale = (SIZE * 1.0) / svar.L;

	if (adjust(oldp, newp)) {
		position tmp, im;
		tmp = getOutPos(oldp, newp);
		tmp = getInterPos(oldp, tmp);
		im.x = o + tmp.x * scale;
		im.y = o - tmp.y * scale;
		oldp.x = o + oldp.x * scale;
		oldp.y = o - oldp.y * scale;
		gdImageSetBrush(img, brushgreen);
		gdImageLine(img, oldp.x, oldp.y, im.x, im.y, gdBrushed);
		tmp = getOppPos(tmp);
		/* Recursion. There might be two borders crossed in one step! */
		pbc_updatePNG(tmp, newp);
	} else {
		newp.x = o + newp.x * scale;
		newp.y = o - newp.y * scale;
		oldp.x = o + oldp.x * scale;
		oldp.y = o - oldp.y * scale;
		gdImageSetBrush(img, brushblue);
		gdImageLine(img, newp.x, newp.y, newp.x, newp.y, gdBrushed);
		gdImageSetBrush(img, brushgreen);
		gdImageLine(img, oldp.x, oldp.y, newp.x, newp.y, gdBrushed);
	}
}

/* Adds new walker position and trajectory to the image. */
void updatePNG()
{
	double scale = (SIZE * 1.0) / svar.L;

	position w, old;	/* Positions on image. */
	w.x = o + walker.pos.x * scale;
	w.y = o - walker.pos.y * scale;
	old.x = o + walker.oldpos.x * scale;
	old.y = o - walker.oldpos.y * scale;

	switch (svar.bc) {
	case 0:	/* No boundaries */
		gdImageSetBrush(img, brushblue);
		gdImageLine(img, w.x, w.y, w.x, w.y, gdBrushed);
		gdImageSetBrush(img, brushgreen);
		gdImageLine(img, old.x, old.y, w.x, w.y, gdBrushed);
		break;
	case 1:	/* Periodic boundaries */
		pbc_updatePNG(walker.oldpos, walker.pos);
		break;
	}
}

/* Draws png to file and frees memory. */
void drawPNG()
{
	gdImagePng(img, pngout);
	fclose(pngout);
	gdImageDestroy(img);
}
