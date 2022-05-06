#include "World/World.h"
#include "World_builder.h"
#include "Materials/Reflective.h"
#include "Materials/Transparent.h"
#include "Materials/GlossyReflector.h"

#include "Cameras/Fisheye.h"
#include "Cameras/Pinhole.h"
#include "Cameras/StereoCamera.h"
#include "Cameras/ThinLens.h"

#include "GeometricObjects/Instance.h"

#include "GeometricObjects/BeveledObjects/BeveledBox.h"
#include "GeometricObjects/Primitives/Rectangle.h"

#include "GeometricObjects/CompoundObjects/Box.h"
#include "GeometricObjects/CompoundObjects/Grid.h"
#include "GeometricObjects/CompoundObjects/RoundRimmedBowl.h"
#include "GeometricObjects/CompoundObjects/SolidCylinder.h"
#include "GeometricObjects/CompoundObjects/SolidCone.h"
#include "GeometricObjects/CompoundObjects/ThickRing.h"

#include "GeometricObjects/PartObjects/ConvexPartSphere.h"
#include "GeometricObjects/PartObjects/OpenPartCylinder.h"
#include "GeometricObjects/Triangles/Triangle.h"

#include "GeometricObjects/Primitives/Plane.h"
#include "GeometricObjects/Primitives/Torus.h"



#include "Lights/Directional.h"
#include "Lights/PointLight.h"

#include "Materials/Matte.h"
#include "Materials/SV_Matte.h"
#include "Materials/Reflective.h"

#include "Textures/Checker3D.h"
#include "Textures/ImageTexture.h"

#include "Samplers/MultiJittered.h"
#include "Samplers/Jittered.h"

#include "Tracers/RayCast.h"

#include "World/Worlds.h"


RGBColor lightRed(1, 0.4, 0.4);
RGBColor darkRed(0.9, 0.1, 0.1);

RGBColor brown(0.71, 0.40, 0.16);
RGBColor redBrown(0.85, 0.6, 0.2);


RGBColor orange(1, 0.6, 0.2);

RGBColor lemon(1, 1, 0.33);
RGBColor yellow(1, 1, 0);
RGBColor darkYellow(0.61, 0.61, 0);

RGBColor lightGreen(0.65, 0.8, 0.30);
RGBColor lightLightGreen(0.85, 1.0, 0.6);
RGBColor green(0, 0.6, 0.3);
RGBColor realGreen(0, 1.0, 0.1);
RGBColor darkGreen(0.0, 0.81, 0.41);

RGBColor  cyan(0, 1, 1);
RGBColor  blue_green(0.1, 1, 0.5);

RGBColor lightLightBlue(0.4, 0.64, 0.82);
RGBColor lightBlue(0.1, 0.4, 0.8);
RGBColor darkBlue(0.0, 0.0, 1.0);

RGBColor lightPurple(0.65, 0.3, 1);
RGBColor darkPurple(0.5, 0, 1);

RGBColor lightLightGrey(0.9);
RGBColor lightGrey(0.7);
RGBColor grey(0.25);
RGBColor darkDarkGrey(0.2, 0.2, 0.2);

RGBColor darkBlack(0, 0, 0);


struct ColorCenterRadius {
    RGBColor color;
    Point3D  center;
    int      radius;
};

void build_spheres_helper(World* w, const std::vector<ColorCenterRadius>& spheres) {
    for (const ColorCenterRadius& s : spheres) {
        add_sphere_helper(w, s.color, s.center, s.radius);
    }
}

void build_spheres(World* w) {
    std::vector<ColorCenterRadius> spheres =
        {
           { yellow,       Point3D(   5,  3,    0),   30 },
           { brown,        Point3D(  45, -7,  -60),   20 },
           { darkGreen,    Point3D(  40, 43, -100),   17 },
           { orange,       Point3D( -20, 28,  -15),   20 },
           { green,        Point3D( -25, -7,  -35),   27 },

           { lightGreen,   Point3D(  20, -27,  -35),  25 },
           { green,        Point3D(  35,  18,  -35),  22 },
           { brown,        Point3D( -57, -17,  -50),  15 },
           { lightGreen,   Point3D( -47,  16,  -80),  23 },
           { darkGreen,    Point3D( -15, -32,  -60),  22 },

           { darkYellow,   Point3D( -35, -37,  -80),  22 },
           { darkYellow,   Point3D(  10,  43,  -80),  22 },
           { darkYellow,   Point3D(  30,  -7,  -80),  10 },  // hidden
           { darkGreen,    Point3D( -40,  48, -110),  18 },
           { brown,        Point3D( -10,  53, -120),  18 },

           { lightPurple,  Point3D(-55, -52, -100),  10 },
           { brown,        Point3D(  5, -52, -100),  15 },
           { darkPurple,   Point3D(-20, -57, -120),  15 },
           { darkGreen,    Point3D( 55, -27, -100),  1 },
           { brown,        Point3D( 50, -47, -120),  15 },

           { lightPurple,  Point3D( 70, -42, -150),  10 },
           { lightPurple,  Point3D(  5,  73, -130),  12 },
           { darkPurple,   Point3D( 66,  21, -130),  13 },
           { lightPurple,  Point3D( 72, -12, -140),  12 },
           { green,        Point3D( 64,   5, -160),  11 },

           { lightPurple,  Point3D( 55,  38, -160),  12 },
           { lightPurple,  Point3D(-73,  -2, -160),  12 },
           { darkPurple,   Point3D( 30, -62, -140),  15 },
           { darkPurple,   Point3D( 25,  63, -140),  15 },
           { darkPurple,   Point3D(-60,  46, -140),  15 },

           { lightPurple,  Point3D(-30,  68, -130),  12 },
           { green,        Point3D( 58,  56, -180),  11 },
           { green,        Point3D(-63, -39, -180),  11 },
           { lightPurple,  Point3D( 46,  68, -200),  10 },
           { lightPurple,  Point3D( -3, -72, -130),  12 }
        };

    build_spheres_helper(w, spheres);
}

void build_sphere_world(World* w) {
    Pinhole* camera = new Pinhole;
    camera->set_eye(0, 0, 500);
    camera->set_lookat(0.0);
    camera->set_view_distance(600.0);
    // use default up vector and uvw
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light();
    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(300, 100, 200);
    lt->scale_radiance(7.0);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_spheres(w);
}


struct ColorBottomTop {
    RGBColor color;
    Point3D  bottom;
    Point3D  top;
};

void build_city_helper(World* w, const std::vector<ColorBottomTop>& buildings) {
    for (const ColorBottomTop& bldg : buildings) {
        add_bb_helper(w, bldg.color, bldg.bottom, bldg.top);
    }
}
void build_city(World* w) {
    std::vector<ColorBottomTop> buildings =
        { { yellow,      Point3D( 1,  1,  0),   Point3D( 2,  2, 60)  },
          { darkPurple,  Point3D( 0,  0,  0),   Point3D( 1,  1, 60)  },
          { grey,        Point3D(-2,  2,  0),   Point3D(-1,  3,  65) },
          { green,       Point3D(-4,  0,  0),   Point3D(-3,  1,  70) },
          { darkPurple,  Point3D( 3,  0,  0),   Point3D( 4,  1,  65) },

          { darkBlue,    Point3D( 3, -4,  0),   Point3D( 4, -3,  70) },
          { darkPurple,  Point3D(-3, -4,  0),   Point3D(-2, -3,  75) },
          { yellow,      Point3D( 3,  3,  0),   Point3D( 4,  4,  70) },
          { green,       Point3D( 0, -3,  0),   Point3D( 1, -2,  70) },
          { darkBlue,    Point3D( 0,  2,  0),   Point3D( 1,  3,  70) },

          { darkBlue,    Point3D(-2,  0,  0),   Point3D(-1,  1,  70) },
          { darkBlue,    Point3D(-4, -3,  0),   Point3D(-3, -3,  80) },
          { grey,        Point3D( 2, -2,  0),   Point3D( 3, -1,  60) },
          { red,         Point3D(-4,  3,  0),   Point3D(-3,  4,  65) },

          { darkBlue,    Point3D(-6, -5,  0),   Point3D(-5, -5,  80) },
          { green,       Point3D (0,  5,  0),   Point3D( 1,  6,  60) },
          { darkPurple,  Point3D( 3,  5,  0),   Point3D( 4,  6,  65) },
          { darkBlue,    Point3D( 4,  1,  0),   Point3D( 5,  2,  70) },
          { lightRed,    Point3D(-5, -3,  0),   Point3D(-4, -2,  75) },
          { green,       Point3D( 5, -2,  0),   Point3D( 6, -1,  60) },

          { green,       Point3D(-2,  4,  0),   Point3D(-1,  5,  70) },
          { darkBlue,    Point3D(-5,  2,  0),   Point3D(-4,  3,  70) },
          { darkBlue,    Point3D(-5,  5,  0),   Point3D(-4,  6,  60) },
          { darkPurple,  Point3D(-5, -2,  0),   Point3D(-4, -1,  60) },
          { green,       Point3D(-2,  -4,  0),  Point3D(-1, -3, 65) },
          { darkBlue,    Point3D(-2,  -2,  0),  Point3D(-1, -1, 70) },
          { darkBlue,    Point3D(-6,  -1,  0),  Point3D(-5,  0, 70) }
        };

    build_city_helper(w, buildings);
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, grey, white, 2);
    w->add_object(plane);
}
void build_city_world(World* w, double distance) {
    Pinhole* camera = new Pinhole;
    camera->set_eye(-0.5, 0, 110);
    camera->set_lookat(-0.5, 0, -10);
    camera->set_view_distance(distance);
    camera->compute_uvw();
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light();
    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(-130, -15, 30);
    lt->scale_radiance(5);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_city(w);
}


#define SPACING 5
#define SIDE 1

void add_checkerboard(World* w, const RGBColor& c1, const RGBColor& c2, int size) {
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, c1, c2, size);
    w->add_object(plane);
}

void build_practical(World *w) {
    for (int i = 0; i < 60; i += SPACING) {
        add_bb_helper(w, orange, Point3D( i, 0, 0),     SIDE, SIDE, 4);
        add_bb_helper(w, orange, Point3D( 0, 3 * SPACING + i, 0), SIDE, SIDE, 4);

        add_bb_helper(w, cyan, Point3D( i, SPACING, 0), SIDE, SIDE, 8);

        add_bb_helper(w, green, Point3D( i,  2 * SPACING, 0), SIDE, SIDE, 16);
    }

    add_checkerboard(w, lightGrey, white, 1);
}
void build_practical_world(World* w, double distance) {
    Pinhole* camera = new Pinhole;
    camera->set_eye(-6, -5, 9);
    camera->set_lookat(-1, 0, 7);
    camera->set_view_distance(distance);    // camera->set_view_distance(800.0);
    camera->set_up_vector(1, 1, 1);
    camera->compute_uvw();
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light();
    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(10, -30, 10);
    lt->scale_radiance(8.5);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_practical(w);
}


void build_sphere_triangle_box(World* w) {
    add_sphere_helper(w, lightGreen, Point3D(1.7, -0.2, 1.7), SIDE/2.5);
    add_bb_helper(w, orange, Point3D( 2, 0, 0), 0.75 * SIDE, SIDE, 2.5);

    std::shared_ptr<Phong> phong = std::make_shared<Phong>();
    phong->set_cd(cyan);
    phong->set_ka(0.5);
    phong->set_kd(0.5);
    phong->set_ks(0.06);
    phong->set_exp(1);

    Triangle* triangle = new Triangle(Point3D(0.7, -1, 0.2), Point3D(3, 0, 1.25), Point3D(1.5, 0.5, 1.75));
    triangle->set_material(phong);
    w->add_object(triangle);

    add_checkerboard(w, lightGrey, white, 1);
}
void build_sphere_triangle_box_world(World* w, CHOICE choice) {
    Pinhole* camera = new Pinhole;
    switch(choice) {
    case A:    // front
        camera->set_eye(1, -4, 2);
        camera->set_lookat(0, 10, 2);
        camera->set_view_distance(150);
        break;
    case B:    // medium
        camera->set_eye(4, -4, 6);
        camera->set_lookat(-4, 4, -10);
        camera->set_view_distance(200);
        break;
    case C:    // overhead
        camera->set_eye(3, -4, 15);        // overhead
        camera->set_lookat(0, 0, -10);
        camera->set_view_distance(100);
        break;
     default:
        throw new std::invalid_argument("Invalid choice\n");
        break;
    }
    camera->set_up_vector(0, 0, 1);
    camera->compute_uvw();
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light();
    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(50, -50, 300);
    lt->scale_radiance(4.0);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_sphere_triangle_box(w);
}


void build_olympic_ring(World* w, Point3D center, double rotation, RGBColor& color) {
    Instance* isring = new Instance(new ThickRing(1.8, 2, 1, 1.1));
    isring->rotate_z(rotation);
    isring->translate(center);
    w->set_material(isring, color);
    w->add_object(isring);
}

void build_olympic_rings(World* w) {
    build_olympic_ring(w, Point3D(-2, 0, 6),   0,  yellow);
    build_olympic_ring(w, Point3D(-1, 2, 6),  30, darkRed);
    build_olympic_ring(w, Point3D( 0, 2, 6),   0,  darkBlack);
    build_olympic_ring(w, Point3D( 1, 2, 6), -30, green);
    build_olympic_ring(w, Point3D( 2, 0, 6),   0,  darkBlue);

    add_checkerboard(w, lightGrey, white, 1);
}
void build_olympic_rings_world(World* w) {
    Pinhole* camera = new Pinhole;
    camera->set_eye(0, 8, 10);
    camera->set_lookat(0, 0, -10);
    camera->set_view_distance(80);
//        ptr->set_eye(1, -4, 2);
//        ptr->set_lookat(0, 10, 2);
//        ptr->set_view_distance(150);

    camera->set_up_vector(0, 0, 1);
    camera->compute_uvw();
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light(1.4);
    w->background_color = white;
    Directional* lt = new Directional();
    lt->set_direction(10, -100, 5);
    lt->scale_radiance(2);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_olympic_rings(w);
}


void thin_lens_helper(World* w, const Point3D& p1, const Point3D& p2,
                      const RGBColor& c1, const RGBColor& c2) {
    Checker3D* check = new Checker3D;
    check->set_size(2.0);
    check->set_color1(c1);
    check->set_color2(c2);

    std::shared_ptr<SV_Matte> matte = std::make_shared<SV_Matte>();
    matte->set_ka(0.5);
    matte->set_kd(0.35);
    matte->set_cd(check);

    Box* b = new Box(p1, p2);
    b->set_material(matte);
    w->add_object(b);
}

void build_thinlens(World* w, double focal_distance) {
    int num_samples = 100;

    w->vp.set_hres(400);
    w->vp.set_vres(300);
    w->vp.set_pixel_size(0.05);
    w->vp.set_sampler(new MultiJittered(num_samples));
    w->vp.set_max_depth(0);

    w->tracer_ptr = new RayCast(w);
    w->background_color = white;

    Ambient* ambient_ptr = new Ambient;
    ambient_ptr->scale_radiance(0.5);
    w->set_ambient_light(ambient_ptr);

    ThinLens* tl = new ThinLens;
    tl->set_sampler(new MultiJittered(num_samples));
    tl->set_eye(0, 6, 50);
    tl->set_lookat(0, 6, 0);
    tl->set_view_distance(40.0);

    tl->set_focal_distance(focal_distance);

    tl->set_lens_radius(1.0);
    tl->compute_uvw();
    w->set_camera(tl);


    Directional* lp = new Directional;
    lp->set_direction(1, 1, 1);
    lp->scale_radiance(7.5);
    lp->set_shadows(true);
    w->add_light(lp);

    thin_lens_helper(w, Point3D(-9, 0, -1),     Point3D(-3, 12, 0),     lemon,      black);
    thin_lens_helper(w, Point3D(-3.25, 0, -25), Point3D(4.75, 14, -24), blue_green, black);
    thin_lens_helper(w, Point3D(8, 0, -49),     Point3D(18, 15, -48),   orange,     black);

    Instance* isplane = new Instance(new Plane(Point3D(0, 0, 0), Normal(0, 1, 0)));
    isplane->rotate_y(90);
    build_checkerboard(isplane, lightGrey, black, 8);

    w->add_object(isplane);
}


void
build_fisheye(World* w, CHOICE choice) {
    int num_samples = 25;

    w->vp.set_hres(600);
    w->vp.set_vres(600);
    w->vp.set_samples(num_samples);

    w->background_color = lightLightBlue;

    w->tracer_ptr = new RayCast(w);

    // pinhole camera for Figure 11.7(a)

    Pinhole* pinHole_ptr = new Pinhole;
    Fisheye* fisheye = new Fisheye;    // fisheye camera for the other parts
    fisheye->set_eye(350, 450, 150);
    fisheye->set_lookat(-20, 300, -110);
    int fov = 120;

    switch(choice) {
    case A:
        pinHole_ptr->set_eye(250, 300, 150);
        pinHole_ptr->set_lookat(-20, 300, -110);
        pinHole_ptr->set_view_distance(250);
        pinHole_ptr->compute_uvw();
        w->set_camera(pinHole_ptr);
        break;
    case B:  fov = 120;  break;
    case C:  fov = 180;  break;
    case D:  fov = 360;  break;
    case E:
        fisheye->set_eye(250, 450, 150);
        fisheye->set_lookat(-20, 250, -110);
        fov = 360;
        break;
    default:
        throw new std::invalid_argument("Invalid choice in fisheye\n");
        break;
    }
    fisheye->set_fov(fov);

/*	// for part (f)
    // for this image the skydome is the only object in the scene
    // you need to comment out the two statements:
    // add_object(grid_ptr);
    // add_object(plane_ptr);

    fisheye->set_eye(0, 0, 0);
    fisheye->set_lookat(0, 1, 0);
    fisheye->set_fov(180);
*/
    fisheye->compute_uvw();
    if (choice != A) {  w->set_camera(fisheye); }

    PointLight* light_ptr1 = new PointLight;
    light_ptr1->set_location(150, 200, 65);
//    light_ptr1->scale_radiance(5.25);
    light_ptr1->scale_radiance(15.25);
    light_ptr1->set_shadows(true);
    w->add_light(light_ptr1);


    // box materials
    std::shared_ptr<Matte> matte1 = std::make_shared<Matte>();
    matte1->set_cd(0, 0.5, 0.5);     // cyan
    matte1->set_ka(0.4);
    matte1->set_kd(0.5);

    std::shared_ptr<Matte> matte2 = std::make_shared<Matte>();
    matte2->set_cd(1, 0, 0);     	  // red
    matte2->set_ka(0.4);
    matte2->set_kd(0.5);

    std::shared_ptr<Matte> matte3 = std::make_shared<Matte>();
    matte3->set_cd(0.5, 0.6, 0);     // green
    matte3->set_ka(0.4);
    matte3->set_kd(0.5);

    Grid* grid = new Grid;    // Construct rows of boxes stored in a grid

    int num_boxes = 40;    // first row
    float wx = 50;
    float wz = 50;
    float h = 150;
    float s = 100;

    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-wx, 0, -(j + 1) * wz - j * s),
                                Point3D(0, h, - j * wz - j * s));
        box->set_material(matte1);
        grid->add_object(box);
    }

    h = 300;    // second row
    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-wx -wx - s, 0, -(j + 1) * wz - j * s),
                                Point3D(-wx - s, h, - j * wz - j * s));
        box->set_material(matte2);
        grid->add_object(box);
    }

    h = 850; 	// third row
    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-wx - 2 * wx - 2 * s, 0, -(j + 1) * wz - j * s),
                                Point3D(-2 * wx - 2 * s, h, - j * wz - j * s));
        box->set_material(matte3);
        grid->add_object(box);
    }

    // a column
    h = 150;
    for (int j = 0; j < num_boxes; j++) {
        Box* box = new Box(	Point3D(-3 * (wx + s) - (j + 1) * wz - j * s, 0, -wx),
                                Point3D(-3 * (wx + s) - j * wz - j * s, h, 0));
        box->set_material(matte1);
        grid->add_object(box);
    }

    grid->setup_cells();
    w->add_object(grid);

    Checker3D* check = new Checker3D;
    check->set_size(2 * wx);
    check->set_color1(0.7);
    check->set_color2(white);

//	SV_Matte* sv_matte1 = new SV_Matte;
    std::shared_ptr<SV_Matte> sv_matte1 = std::make_shared<SV_Matte>();
//    sv_matte1->set_ka(0.20);
    sv_matte1->set_ka(1.0);
    sv_matte1->set_kd(0.50);
    sv_matte1->set_cd(check);
    Plane* plane = new Plane(Point3D(0, 1, 0), Normal(0, 1, 0));
    plane->set_material(sv_matte1);
    w->add_object(plane);
}

    // skydome with clouds

//	Image* image = new Image;
//	image->read_ppm_file("CloudsSmall.ppm");

//	SphericalMap* spherical_map = new SphericalMap;

//	ImageTexture* image_texture = new ImageTexture(image);
//	image_texture->set_mapping(spherical_map);

////	SV_Matte* sv_matte2 = new SV_Matte;
//    std::shared_ptr<SV_Matte> sv_matte2 = std::make_shared<SV_Matte>();
//	sv_matte2->set_ka(1);
//	sv_matte2->set_kd(0.85);
//	sv_matte2->set_cd(image_texture);

//	Instance* sphere = new Instance(new Sphere);
//	sphere->scale(1000000);
//	sphere->set_material(sv_matte2);
//	w->add_object(sphere);
//}


void build_stereo(World* w, CHOICE choice) {
  int num_samples = 1;

  w->vp.set_hres(200);
  w->vp.set_vres(200);
  w->vp.set_pixel_size(0.05);
  w->vp.set_samples(num_samples);

  w->tracer_ptr = new RayCast(w);

  float vpd = 100;  // view plane distance for 200 x 200 pixel images

  Pinhole* left_camera = new Pinhole;
  left_camera->set_view_distance(vpd);

  Pinhole* right_camera = new Pinhole;
  right_camera->set_view_distance(vpd);

  StereoCamera* stereo = new StereoCamera;
//  Stereo* stereo = new Stereo;
  if (choice == A) {
      stereo->set_left_camera(left_camera);
      stereo->set_right_camera(right_camera);
      stereo->use_parallel_viewing();
  } else if (choice == B) {
      stereo->set_left_camera(right_camera);
      stereo->set_right_camera(left_camera);
      stereo->use_transverse_viewing();
  } else {
      throw new std::invalid_argument("invalid choice\n");
  }
  stereo->set_pixel_gap(5);
  stereo->set_eye(5, 0, 100);
  stereo->set_lookat(0);
  stereo->compute_uvw();
  stereo->set_stereo_angle(0.75);  // deg, not radians
  stereo->setup_cameras();
  w->set_camera(stereo);

//  PointLight* lt = new PointLight;
  Directional* lt = new Directional;
  lt->set_direction(100, 100, 100);
  lt->scale_radiance(3);
//  lt->scale_radiance(3);
  lt->set_shadows(true);
  w->add_light(lt);

  double exp_ = 1;
  double ka_ = 0.2;
  double kd_ = 0.2;
  double ks_ = 0.06;

  std::shared_ptr<Phong> phong1 = std::make_shared<Phong>();
  phong1->set_cd(cyan);
  phong1->set_ka(ka_);
  phong1->set_kd(kd_);
  phong1->set_ks(ks_);
  phong1->set_exp(exp_);

  std::shared_ptr<Phong> phong2 = std::make_shared<Phong>();
  phong2->set_cd(redBrown);
  phong2->set_ka(ka_);
  phong2->set_kd(kd_);
  phong2->set_ks(ks_);
  phong2->set_exp(exp_);

  std::shared_ptr<Phong> phong3 = std::make_shared<Phong>();
  phong3->set_cd(yellow);
  phong3->set_ka(ka_);
  phong3->set_kd(kd_);
  phong3->set_ks(ks_);
  phong3->set_exp(exp_);

  Sphere* sphere1 = new Sphere(Point3D(0, 0, 35), 0.75);
  sphere1->set_material(phong1);
  w->add_object(sphere1);

  Sphere* sphere2 = new Sphere(Point3D(0), 2);
  sphere2->set_material(phong2);
  w->add_object(sphere2);

  Sphere* sphere3 = new Sphere(Point3D(1.5, 0, -80), 2);
  sphere3->set_material(phong3);
  w->add_object(sphere3);
}


void build_mcdonalds(World* w) {
    std::shared_ptr<Phong> phong1 = std::make_shared<Phong>();
    phong1->set_cd(yellow);
    phong1->set_ka(0.3);
    phong1->set_kd(0.3);
    phong1->set_ks(0.06);
    phong1->set_exp(1);

    Instance* ring1 = new Instance(new ThickRing(2, 4, 5, 6));
    Instance* ring2 = new Instance(new ThickRing(2, 4, 5, 6));
    ring1->translate(Point3D(0, 12, -1));
    ring2->translate(Point3D(0, 0, -1));
    ring1->set_material(phong1);
    ring2->set_material(phong1);
    w->add_object(ring1);
    w->add_object(ring2);

    std::shared_ptr<Phong> phong2 = std::make_shared<Phong>();
    phong2->set_cd(lightBlue);
    phong2->set_ka(0.5);
    phong2->set_kd(0.5);
    phong2->set_ks(0.06);
    phong2->set_exp(2);

    Instance* cone = new Instance(new SolidCone(5, 2));
    cone->rotate_x(90);
    cone->translate(Point3D(2, -3, 0));
    cone->set_material(phong2);
    w->add_object(cone);
    add_checkerboard(w, darkRed, white, 1);

    add_sphere_helper(w, red, Point3D(7, -1, 2.5), 2.5);
    add_bb_helper(w, orange, Point3D(7, 3, 0), 4, 2, 5);
}

void build_mcdonalds_world(World* w) {
    Pinhole* camera = new Pinhole;
    camera->set_eye(-3, -3, 6);
    camera->set_lookat(-1, 0, 2);
    camera->set_view_distance(50);    // camera->set_view_distance(800.0);
    camera->set_up_vector(0, 0, 1);
    camera->compute_uvw();
    w->set_camera(camera);

    w->init_viewplane();

    w->init_ambient_light();
    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(-20, 10, 30);
    lt->scale_radiance(10.5);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_mcdonalds(w);
}

void build_figure_10_10(World* w, CHOICE choice) {
    switch(choice) {
        case A: build_thinlens(w, 50.0); break;
        case B: build_thinlens(w, 74.0); break;
        case C: build_thinlens(w, 98.0); break;
        default: throw new std::invalid_argument("Invalid choice.\n");
    }
}

void build_figure_11_7(World* w, CHOICE choice) {
    qDebug("this is in 11_7\n");
    switch(choice) {
        case A: case B: case C: case D: case E: build_fisheye(w, choice); break;
        default: throw new std::invalid_argument("Invalid choice.\n");
    }
}

void build_figure_12_12(World* w, CHOICE choice) {
    qDebug("this is in 12_12\n");
    switch(choice) {
        case A: case B: build_stereo(w, choice); break;
        default: throw new std::invalid_argument("Invalid choice.\n");
    }
}


struct RingDims {
    RingDims(double bottom_, double top_, double inner_, double outer_)
        : bottom(bottom_), top(top_), inner(inner_), outer(outer_) { }
    double bottom, top;
    double inner, outer;
};

void build_cone_helper(World* w, const Point3D& posn, const RGBColor& color, double h, double r) {
    Instance* iscone = new Instance(new SolidCone(h,r));
    iscone->rotate_y(0);
    iscone->rotate_z(0);
    iscone->rotate_x(90);
    iscone->translate(posn);

    std::shared_ptr<Phong> phong = std::make_shared<Phong>();
    phong->set_ka(0.75);
    phong->set_kd(1.25);
    phong->set_cd(color);
    phong->set_ks(0.25);
    phong->set_exp(1.5);

    iscone->set_material(phong);
//    w->set_material(iscone, color);
    w->add_object(iscone);
}

void build_cylinder_helper(World* w, const Point3D& posn, const RGBColor& color, double b, double t, double r) {
    Instance* iscylinder = new Instance(new SolidCylinder(b,t,r));
    iscylinder->rotate_y(0);
    iscylinder->rotate_z(0);
    iscylinder->rotate_x(90);
    iscylinder->translate(posn);
//    iscylinder->set_material(m_ptr);

    std::shared_ptr<Phong> phong = std::make_shared<Phong>();
    phong->set_ka(0.25);
    phong->set_kd(0.75);
    phong->set_cd(green);
    phong->set_ks(0.25);
    phong->set_exp(1.5);

    w->set_material(iscylinder, color);
    w->add_object(iscylinder);
}

void build_ring_helper(World* w, const Point3D& posn, const RGBColor& color, const RingDims& rd, int r, std::shared_ptr<Material> m_ptr) {
    Instance* isring = new Instance(new ThickRing(rd.bottom, rd.top, rd.inner, rd.outer));
    isring->rotate_y(0);
    isring->rotate_z(r);
    isring->translate(posn);
    isring->set_material(m_ptr);
    w->set_material(isring, color);
    w->add_object(isring);
}

void build_mcdonalds_alberto(World* w){
    //camera
    Pinhole* ptr = new Pinhole;
    ptr->set_eye(-2, -12, 14);        // overhead
    ptr->set_lookat(0, 10, -10);     // overhead
    ptr->set_view_distance(200);    // overhead
    ptr->set_up_vector(0, 0, 1);
    ptr->compute_uvw();
    w->set_camera(ptr);

    //viewplane
    int num_samples = 25;
    w->vp.set_hres(VIEWPLANE_HRES);
    w->vp.set_vres(VIEWPLANE_VRES);
    w->vp.set_sampler(new Jittered(num_samples));
    w->vp.set_pixel_size(0.5);
    w->vp.set_samples(num_samples);

    //lights
    Ambient* ambient_ptr = new Ambient;
    ambient_ptr->scale_radiance(0.2);
    w->set_ambient_light(ambient_ptr);
    w->background_color =  black;//RGBColor(0.9, 0.9, 0.9);
    w->tracer_ptr = new RayCast(w);

    Directional* lt = new Directional();
    lt->set_shadows(true);
    lt->set_direction(-30, 7, 10);
    lt->scale_radiance(8.5);
    w->add_light(lt);

    //plane
    float ka = 0.25;
    float kd = 0.75;
    RGBColor grey(0.25);

    std::shared_ptr<Phong> phong_ptr36 = std::make_shared<Phong>();
    phong_ptr36->set_ka(ka);
    phong_ptr36->set_kd(kd);
    phong_ptr36->set_cd(grey);
    phong_ptr36->set_ks(0.25);
    phong_ptr36->set_exp(1.5);

    Plane* plane_ptr = new Plane(Point3D(0, 0, -150), Normal(0, 0, 1));
    plane_ptr->set_material(phong_ptr36);
    w->add_object(plane_ptr);

    //build
    std::shared_ptr<Reflective> reflect1 = std::make_shared<Reflective>();
    reflect1->set_kr(2.5);
    reflect1->set_ka(1.25);
    reflect1->set_kd(1.75);
    reflect1->set_cd(lightBlue);

    Sphere* sphere2 = new Sphere(Point3D(2.5, 0.8, 4), 2.5);
    sphere2->set_material(reflect1);
    w->add_object(sphere2);

    RingDims rd = RingDims(1, 2, 6.5, 8);
    build_ring_helper(    w,         Point3D(  -2,    0,  -0.5), yellow, rd, 50, phong_ptr36);
    build_ring_helper(    w,         Point3D(-12,    6,   1),   yellow, rd, 45, phong_ptr36);
    add_bb_helper(        w, orange, Point3D(  0,    6,   0),   Point3D(3, 7, 6));
    build_cone_helper(    w,         Point3D(  -2,   3.5, 0),   cyan, 4.0, 1.5);
    build_cone_helper(    w,         Point3D(  2,   -2.5, 0),   darkBlue,   5.0, 1.5);
    build_cylinder_helper(w,         Point3D( -2.5, -1,   0),   green, 0.0, 3.0, 1.0);
    add_triangle_helper(  w, red,    Point3D( -2.8,  2.5, 2.5), Point3D(-2.5, -7.5, 0.5), Point3D(-0.5, -3, 1.5));

    add_checkerboard(w, red, white, 1);
}

void build_axis(World* w, double length, double width) {
    add_bb_helper(w, red, Point3D(0, 0, 0),  length, width, width);
    add_triangle_helper(w, red, Point3D(length, 0, 1.2 * width), Point3D(length, 0, -0.6 * width), Point3D(length + 1.2 * width, 0, 0.6 * width));

    add_bb_helper(w, darkBlue, Point3D(0, 0, 0),  width, length, width);
    add_triangle_helper(w, darkBlue, Point3D(0, length, 1.2 * width), Point3D(0, length, -0.6 * width), Point3D(0, length + 1.2 * width, 0.6 * width));
}

//void build_sundial(World* w, double radius) {
//    double thickness = 0.5;
//    build_axis(w, 1.5 * radius, thickness);

////    add_triangle_helper(w, lightRed, Point3D(-3, -6, 4.2), Point3D(-2, 5, 1.6), Point3D(0, 0, -1));
////    add_sphere_helper(w, lightLightGreen, Point3D(0, 0, 0), 4);
//    add_bb_helper(w, red, Point3D(-1, -1, 0),  2, 2, 10);

//    Instance* iscone = new Instance(new SolidCone(4, 1.2));
//    iscone->rotate_x(90);
//    iscone->translate(0, 0, 10);
//    w->set_material(iscone, darkBlue);
//    w->add_object(iscone);

//    Instance* isring = new Instance(new ThickRing(-0.5, 0.5, radius - 0.5, radius));
//    w->set_material(isring, yellow);
//    isring->translate(0, 0, 0);
//    isring->rotate_x(90);
//    w->add_object(isring);

//    add_bb_helper(w, red, Point3D(0, 0, 0),  radius, thickness, thickness / 2.0);

//    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
//    build_checkerboard(plane, darkBlue, white, 8);
//    w->add_object(plane);
//}

void build_sundial(World* w, double height, double radius, double lat) {
    double post_side = 3.0;
    Point3D origin(0,0,0);
    double pi = 3.141592;
    radius = 15;

    Plane* plane = new Plane(Point3D(-30, -30, -height), Normal(0, 0, 1));
    build_checkerboard(plane, grey, white, 8);
    w->add_object(plane);

    Compound* sundial = new Compound();

    Instance* ispost = new Instance(new Box(Point3D(-post_side/2.0, -post_side/2.0, -height),
                                            Point3D(post_side, post_side, 1)));
    ispost->translate(-post_side/2, -post_side/2, 0);
    w->set_material(ispost, darkBlue);
    sundial->add_object(ispost);


    Instance* isface = new Instance(new ThickRing(0.0, 0.2, 1, radius));
    isface->rotate_x(90 - lat);
    isface->translate(0, 0, 0);
    build_checkerboard(isface, darkBlue, white, 1);
    sundial->add_object(isface);

    double side = 1;
    double gnomon_height = 8;
    Instance* isgnomon = new Instance(new Box(Point3D(-side/2.0, -side/2.0, 0),
                                              Point3D(side, side, gnomon_height)));
    isgnomon->translate(-side/2, -side/2, 0);
    isgnomon->rotate_x(-lat);
    w->set_material(isgnomon, yellow);
    sundial->add_object(isgnomon);

    Instance* iscone = new Instance(new SolidCone(4, 1));
    build_checkerboard(iscone, red, white, 0.5);
    iscone->rotate_x(90 - lat);
    iscone->translate(0, gnomon_height * sin(lat/180.0 * pi), gnomon_height * cos(lat/180.0 * pi));
    sundial->add_object(iscone);

    Instance* isring = new Instance(new ThickRing(0.0, 0.5, radius - 0.1, radius));
        isring->rotate_x(90 - lat);
    isface->translate(0, 0, 0);
    w->set_material(isring, yellow);
    sundial->add_object(isring);

    double r = 1;
    double phi = 0.0;
    while (phi < 2 * pi) {
        Instance* i = new Instance(new Sphere(Point3D(radius * cos(phi), radius * sin(phi),0), r));
        i->rotate_x(-lat);
        w->set_material(i, red);
        sundial->add_object(i);
        phi += pi / 12.0;
    }

    double thinside = 0.4;
    Box* box = new Box(Point3D(-thinside/2.0, -thinside/2.0, 0), Point3D(radius, thinside, thinside));
    w->set_material(box, yellow);
    sundial->add_object(box);

    w->add_object(sundial);
}

void build_sundial_world(World* w, double height, double radius, double lat) {
    Pinhole* ptr = new Pinhole;
    ptr->set_eye(-35, 30, 80);
//    ptr->set_eye(-35, 30, 0);
    ptr->set_lookat(0, 0, 6);
    ptr->set_view_distance(250);
    ptr->set_up_vector(0, 0, 1);
    ptr->compute_uvw();
    w->set_camera(ptr);
    w->init_viewplane();

    w->init_ambient_light(0.4);

    Directional* lt = new Directional;
    lt->set_shadows(true);
//    lt->set_direction(500, 120, 30);
//    lt->set_direction(20, 120, 30);
//    lt->set_direction(0, 120, 30);
    lt->set_direction(20, 20, 5);
    lt->scale_radiance(11.0);

    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);

    w->init_plane();

    build_sundial(w, height, radius, lat);
}

Instance* add_torus_helper(World* w, const RGBColor& color, double a, double b,
                           Point3D& location, Point3D scale) {
    Instance* istorus = new Instance(new Torus(a, b));
    w->set_material(istorus, color);
    istorus->rotate_x(90);
    istorus->rotate_y(65);//istorus->rotate_y(65);
    istorus->scale(scale);
    istorus->translate(location);
    return istorus;
}
Instance* add_body_helper(World* w, const RGBColor& color, double a, double b,
                           Point3D location, Point3D scale) {
    Instance* issaucer5_3 = new Instance(new Torus(a,b));
    w->set_material(issaucer5_3, color);
    issaucer5_3->rotate_z(90);
    issaucer5_3->rotate_y(-4);///
    issaucer5_3->scale(scale);
    issaucer5_3->translate(location);
    return issaucer5_3;
}

void build_voyager(World* w) {
    //1.Ground - big checkerboard
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, grey, white, 8);
    Instance* planer = new Instance(plane);
    planer->translate(Point3D(0,0,-80));
    w->add_object(planer);

    Compound* voyager = new Compound();
    Compound* tail = new Compound();
    Compound* head = new Compound();

    //2.Top of head- smallest with the hat
    //Main head
    Instance* issphere = new Instance(new ConvexPartSphere(Point3D(), 220, 0, 360, 0, 15));
    w->set_material(issphere, darkDarkGrey);//red
    issphere->rotate_x(90);
    issphere->scale(1,0.7,1);
    issphere->translate(Point3D(0, 0, -195));
    head->add_object(issphere);

    //Head-top hat (centralized controller)
    Instance* hat = new Instance(new Box(Point3D(0,0,0),Point3D(4,4,5)));
    hat->translate(Point3D(0, -2, 22));
    w->set_material(hat, lightGrey);//yellow
    head->add_object(hat);

    //3.Initialize location for head addon and body-tail addon build up
    Point3D low_1_location(6, 0, 17);
    Point3D low_2_location(8, 0, 17);
    Point3D low_3_location(11, 0, 17);
    Point3D low_4_location(15, 0, 17);
    Point3D low_5_location(18, 0, 17);

    Point3D location(0, 0, 20);
    Point3D high_location(4, 0, 20);

    //4.Head addon approximation
    head->add_object(add_torus_helper(w, darkDarkGrey, 30, 5, low_1_location, Point3D(3, 1, 0.1)));//grey
    head->add_object(add_torus_helper(w, darkDarkGrey, 30, 5, low_2_location, Point3D(3, 1, 0.1)));//darkBlue
    head->add_object(add_torus_helper(w, darkDarkGrey, 30, 8, low_3_location, Point3D(2.3, 0.75, 0.1)));//lightPurple
    head->add_object(add_torus_helper(w, darkDarkGrey, 30, 12, low_4_location, Point3D(1.7, 0.5, 0.1)));//red
    head->add_object(add_torus_helper(w, darkDarkGrey, 30, 15, low_5_location, Point3D(1.4, 0.35, 0.1)));//red

    //5.Body-Tail Connector
    //main body-tail
    Instance* issaucer4 = new Instance(new Torus(30, 18));
    w->set_material(issaucer4, darkDarkGrey);//blue_green
    issaucer4->rotate_x(90);
    issaucer4->scale(1.25, 0.3, 0.2);
    issaucer4->translate(Point3D(45, 0, 17));
    tail->add_object(issaucer4);

    //Body-tail addon approximation
    Instance* issaucer5_1 = add_body_helper(w,darkDarkGrey, 30, 30, Point3D(36, 0, 21), Point3D(1, 0.2, 0.1));//lightGrey
    tail->add_object(issaucer5_1);
    Instance* issaucer5_2 = add_body_helper(w,darkDarkGrey, 30, 30, Point3D(40, 0, 20), Point3D(1, 0.2, 0.1));//grey
    tail->add_object(issaucer5_2);
    Instance* issaucer5_3 = add_body_helper(w,darkDarkGrey, 30, 30, Point3D(46, 0, 19.5), Point3D(1, 0.2, 0.1));
    tail->add_object(issaucer5_3);
    Instance* issaucer5_4 = add_body_helper(w,darkDarkGrey, 30, 30, Point3D(7, 0, 18), Point3D(1, 0.2, 0.1));//realGreen
    tail->add_object(issaucer5_4);

    //6.Hydrogen carriers x 2
    //outer-layer
    Instance* iscarrier1 = new Instance(new SolidCylinder(0,15,4));
    w->set_material(iscarrier1, darkDarkGrey);//orange
    iscarrier1->rotate_z(-90);
    //inner-layer
    Instance* iscarrier1_1 = new Instance(iscarrier1->clone());
    iscarrier1_1->scale(Point3D(1.5, 0.7, 0.5));
    //...and real position
    iscarrier1->translate(Point3D(80, 25, 18));
    iscarrier1_1->translate(Point3D(76, 25, 18));
    //..before showing
    tail->add_object(iscarrier1);
    tail->add_object(iscarrier1_1);

    //we need 2 of those set, so..
    Instance* iscarrier2 = new Instance(new SolidCylinder(0,15,4));//outer-layer
    w->set_material(iscarrier2, darkDarkGrey);//orange
    iscarrier2->rotate_z(-90);

    Instance* iscarrier2_1 = new Instance(iscarrier2->clone()); //inner-layer
    iscarrier2_1->scale(Point3D(1.5, 0.7, 0.5));
    iscarrier2->translate(Point3D(80, -25, 18));
    iscarrier2_1->translate(Point3D(76, -25, 18));

    tail->add_object(iscarrier2);
    tail->add_object(iscarrier2_1);

    //7.Carrier-Tail Connector x2
    Instance* connector1 = new Instance(new Box(Point3D(0,0,0),Point3D(5,15,5)));
    connector1->rotate_z(+7);
    connector1->translate(Point3D(59, +02.5, 40));
    connector1->scale(1.5,1.5,0.4);
    w->set_material(connector1, darkDarkGrey);//cyan
    tail->add_object(connector1);

    Instance* connector2 = new Instance(new Box(Point3D(0,0,0),Point3D(5,15,5)));
    connector2->rotate_z(-7);
    connector2->translate(Point3D(57, -17.5, 40));
    connector2->scale(1.5,1.5,0.4);
    w->set_material(connector2, darkDarkGrey);//cyan
    tail->add_object(connector2);

    //8. Have fun with compartments
    Instance* tailer = new Instance(tail);
    Instance* header = new Instance(head);

    header->scale(Point3D(1,1,1.3));
    header->translate(Point3D(-5,0,0));
    header->rotate_y(-2);

    voyager->add_object(header);
    voyager->add_object(tailer);

    //XII.Time for sampling angle viewing
    Instance* craft_sample = new Instance(voyager);
    Point3D scaler = Point3D(0.6,0.6,0.6);
    craft_sample->scale(scaler);//smaller for easier rendering
//    w->add_object(craft_sample);

    //Overhead
    Instance* overhead_craft = new Instance(craft_sample->clone());
    overhead_craft->rotate_z(45);
    overhead_craft->translate(Point3D(0,90,0));
    w->add_object(overhead_craft);

    //Front
    Instance* front_craft = new Instance(craft_sample->clone());
    front_craft->rotate_z(45);
    front_craft->rotate_y(90);
    front_craft->rotate_x(-45);

    //customized angle view @ selected coord
    front_craft->rotate_x(+18);
    front_craft->rotate_z(+35);
    front_craft->translate(Point3D(90,0,0));
    front_craft->rotate_y(-45);
    w->add_object(front_craft);

    //Side
    Instance* side_craft = new Instance(craft_sample->clone());
    side_craft->rotate_x(-90);
    side_craft->rotate_z(-45);
    side_craft->translate(Point3D(-90,0,0));
    w->add_object(side_craft);

    //Back
    Instance* back_craft = new Instance(craft_sample->clone());
    back_craft->rotate_x(-90);
    back_craft->rotate_y(-90);
    back_craft->rotate_z(-45);
    //customized angle view @ selected coord
    back_craft->rotate_z(-45);
    back_craft->rotate_y(-20);
    back_craft->rotate_z(+45);
    back_craft->translate(Point3D(0,-90,0));
    back_craft->rotate_x(-20);
    back_craft->rotate_z(-03);
    w->add_object(back_craft);

}

void build_voyager_world(World* w, int choice) {
    //1.Camera
    Pinhole* ptr = new Pinhole;
    //1.1.Eye at
    switch(choice) {
        case 0: ptr->set_eye(20, 0, 400);   break;  //top 250@Z original
        case 1: ptr->set_eye(-150, 0, 21);  break;  //front
        case 2: ptr->set_eye(0, -300, 21);  break;  //side
        case 3: ptr->set_eye(250, 0, 23);   break;  // back
    }
    //1.2.Look at
    ptr->set_lookat(0, 0, 10);

    //1.3.Viewing distance
    ptr->set_view_distance(250);

    //1.4.Normal vector
    ptr->set_up_vector(0, 0, 1);
    ptr->compute_uvw();
    w->set_camera(ptr);

    //2.Viewplane ft. Light
    w->init_viewplane();
    w->init_ambient_light(0.4);
    Directional* lt = new Directional;
    lt->set_shadows(true);

    switch(choice) {
        case 0: lt->set_direction(50, 50, 100);   break;  //top
        case 1: lt->set_direction(-150, 10, 150);  break;  //front
        case 2: lt->set_direction(30, -50, 60);   break;  //side
        case 3: lt->set_direction(30, -20, 80);    break;  //back
    }
    lt->scale_radiance(11.0);
    w->add_light(lt);

    //3.Rays
    w->tracer_ptr = new RayCast(w);
    w->init_plane();
    build_voyager(w);
}

void build_transparent(World* w, const Point3D& ball) {
    Plane* plane = new Plane(Point3D(-30,-30,0), Normal(0,0,1));
    build_checkerboard(plane, grey, white, 20);
    w->add_object(plane);

    std::shared_ptr<Transparent> glass = std::make_shared<Transparent>();
    glass->set_ks(0.5);
    glass->set_exp(2000);
    glass->set_ior(1.5);
    glass->set_kr(0.1);
    glass->set_kt(0.9);

    Instance* is = new Instance(new Sphere(ball, 3));
    w->set_material(is, red);
    is->set_material(glass);
    w->add_object(is);
}

void set_viewpoint(World* w, Point3D& target, VIEWPOINT view_choice, double distance, double view_distance) {
    Pinhole* ptr = new Pinhole;
    ptr->set_view_distance(view_distance);
    double x=target.x;
    double y=target.y;
    double z=target.z;

    Point3D origin = Point3D(0,0,0);
    add_bb_helper(w,red,origin,30,2,1);//x
    add_bb_helper(w,darkBlue,origin,2,30,1);//y

    switch(view_choice) {
        case OVERHEAD:      z+=distance; break;
        case UNDERNEATH:    z-=distance; break;
        case FRONT:         y+=distance; break;
        case BACK:          y-=distance; break;
        case LEFT:          x-=distance; break;
        case RIGHT:         x+=distance; break;
    default: throw new std::invalid_argument("Invalid choice\n"); break;
    }
    x -= 0.001;
    y -= 0.001;
    ptr->set_eye(Point3D(x,y,z));
    ptr->set_lookat(target);
    ptr->set_up_vector(0, 0, 1);
    ptr->compute_uvw();
    w->set_camera(ptr);
}

void build_transparent_world(World* w) {
    Point3D ball(0,0,50);
    set_viewpoint(w, ball, OVERHEAD, 200, 300);
    w->init_viewplane();
    w->init_ambient_light(0.4);

    Directional* lt = new Directional;
    lt->set_shadows(true);
    lt->set_direction(20,20,5);
    lt->scale_radiance(11);
    w->add_light(lt);

    w->tracer_ptr = new RayCast(w);
    w->init_plane();
    build_transparent(w, ball);

}

void build_working_desk_world(World* w, VIEWPOINT choice) {
    //1.Camera
    Point3D target = Point3D(-5,0,10);

    //1.1.Eye at
    set_viewpoint(w, target, choice, 250, 250);

    //2.Viewplane ft. Light
    w->init_viewplane();

    //3.Light
    w->init_ambient_light(0.4);
    Directional* lt = new Directional;
    lt->set_shadows(true);

    lt->set_direction(50, 50, 100);
    lt->scale_radiance(11.0);
    w->add_light(lt);

    //3.Rays
    w->tracer_ptr = new RayCast(w);
    w->init_plane();
    build_working_desk(w);
}

void add_bb_to_compound(World* w, Compound* cp, RGBColor color,
                        Point3D p0, double dx, double dy, double dz) {
    Point3D p1 = Point3D(p0.x + dx, p0.y + dy, p0.z + dz);
    BeveledBox* bb = new BeveledBox(p0, p1, 0.2);
    w->set_material(bb, color);
    cp->add_object(bb);
}

#define KEY_WIDTH 4
#define KEY_LENGTH 4
#define KEY_SPACE 2
#define KEY_HEIGHT 2
#define KEY_SPACING 6
#define KEY_HALF_WIDTH 2
#define KEY_1_WIDTH 1
#define KEY_1_LENGTH 1
#define KEY_HALF_LENGTH 2
#define KEY_HEIGHT 2
#define KEY_1_HEIGHT 1
void build_working_desk(World* w) {
    //1.Ground - big checkerboard
    //============================================================
    Plane* plane = new Plane(Point3D(-30, -30, 0), Normal(0, 0, 1));
    build_checkerboard(plane, grey, white, 8);
    Instance* planer = new Instance(plane);
    //planer->translate(Point3D(0,0,-40));
    //w->add_object(planer);

    //============================================================
    //2.Flat Matte Keyboard
    Compound* cpkeyboard = new Compound();
    Instance* iskeyboard = new Instance(cpkeyboard);
    int key_row = 0;
    int key_column = 0;
    int key_height = 0;
    RGBColor menu_key_color = cyan;
    RGBColor normal_key_color = darkDarkGrey;
    //1st - menu
    for (int i = 0; i < 14; i += 1) //SPACING = 5, preset above //x-ver, y-hor, z-up
        add_bb_to_compound(w, cpkeyboard, menu_key_color,
                           Point3D( key_row * KEY_SPACING, key_column + i * KEY_SPACING, key_height),
                           KEY_HALF_WIDTH, KEY_LENGTH, KEY_HEIGHT);

    //2nd - #
    key_row++;
    //1st key of
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
                       Point3D( key_row * (KEY_HALF_WIDTH + KEY_SPACE), key_column, key_height),
                       KEY_WIDTH, KEY_HALF_LENGTH, KEY_HEIGHT);
    key_column++;
    for (int i = 0; i < 12; i += 1) //12 keys
        add_bb_to_compound(w, cpkeyboard, normal_key_color,
        Point3D( key_row * (KEY_HALF_WIDTH + KEY_SPACE), key_column * (KEY_HALF_LENGTH + KEY_SPACE) + i * KEY_SPACING, key_height),
        KEY_WIDTH, KEY_LENGTH, KEY_HEIGHT);
    //last key
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
    Point3D( key_row * (KEY_HALF_WIDTH + KEY_SPACE), key_column * (KEY_HALF_LENGTH + KEY_SPACE) + 12 * KEY_SPACING, key_height),
    KEY_WIDTH, KEY_LENGTH + KEY_HALF_LENGTH, KEY_HEIGHT);

    //3rd - qwe...
    key_row++; key_column = 0;
    for (int i = 0; i < 14; i += 1) {//13 keys
        RGBColor color = (i==0 || i==13) ? menu_key_color : normal_key_color;
        add_bb_to_compound(w, cpkeyboard, color,
        Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, key_column * (KEY_LENGTH + KEY_SPACE) + i * KEY_SPACING, key_height),
        KEY_WIDTH, KEY_LENGTH, KEY_HEIGHT);
    }

    //4th - asd...
    key_row++;
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
                       Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, key_column, key_height),
                       KEY_WIDTH, KEY_LENGTH + KEY_HALF_LENGTH, KEY_HEIGHT);
    for (int i = 0; i < 11; i += 1)
        add_bb_to_compound(w, cpkeyboard, normal_key_color,
        Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, KEY_SPACING + KEY_HALF_LENGTH + i * KEY_SPACING, key_height),
        KEY_WIDTH, KEY_LENGTH, KEY_HEIGHT);
    //last key
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
                       Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, KEY_SPACING + KEY_HALF_LENGTH + 11 * KEY_SPACING, key_height),
                       KEY_WIDTH, KEY_LENGTH + KEY_LENGTH, KEY_HEIGHT);

    //5th - zxc...
    key_row++;
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
                       Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, key_column, key_height),
                       KEY_WIDTH, KEY_LENGTH + KEY_LENGTH, KEY_HEIGHT);
    for (int i = 0; i < 10; i += 1)
        add_bb_to_compound(w, cpkeyboard, normal_key_color,
        Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, KEY_SPACING + KEY_LENGTH + i * KEY_SPACING, key_height),
        KEY_WIDTH, KEY_LENGTH, KEY_HEIGHT);
    //last key
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
                       Point3D( key_row * KEY_SPACING - KEY_HALF_WIDTH, KEY_SPACING + KEY_LENGTH + 10 * KEY_SPACING, key_height),
                       KEY_WIDTH, KEY_LENGTH + KEY_LENGTH + KEY_LENGTH, KEY_HEIGHT);

    //6th - options/functions
    key_row++;
    for (int i = 0; i < 4; i += 1)
        add_bb_to_compound(w, cpkeyboard, menu_key_color,
                           Point3D( key_row * KEY_SPACING - KEY_1_WIDTH,  i * (KEY_SPACING+KEY_1_LENGTH), key_height),
                           KEY_WIDTH + KEY_1_WIDTH, KEY_LENGTH + KEY_1_LENGTH, KEY_HEIGHT);
    add_bb_to_compound(w, cpkeyboard, normal_key_color,
    Point3D( key_row * KEY_SPACING - KEY_1_WIDTH,  4 * (KEY_SPACING+KEY_1_LENGTH), key_height),
    KEY_WIDTH + KEY_1_WIDTH, 5 * KEY_LENGTH, KEY_HEIGHT);
    for (int i = 0; i < 2; i += 1)
        add_bb_to_compound(w, cpkeyboard, menu_key_color,
        Point3D( key_row * KEY_SPACING - KEY_1_WIDTH, 7 * KEY_SPACING+ 8 * KEY_1_LENGTH + i * (KEY_SPACING+KEY_1_LENGTH), key_height),
        KEY_WIDTH + KEY_1_WIDTH, KEY_LENGTH + KEY_1_LENGTH, KEY_HEIGHT);
    //left, right, down
    for (int i = 0; i < 3; i += 1)
        add_bb_to_compound(w, cpkeyboard, menu_key_color,
        Point3D( key_row * KEY_SPACING + KEY_HALF_WIDTH, 7 * KEY_SPACING+ 8 * KEY_1_LENGTH + (i+2) * KEY_SPACING+ (i+1) * KEY_1_LENGTH, key_height),
        KEY_HALF_WIDTH, KEY_LENGTH + KEY_1_LENGTH, KEY_HEIGHT);
    //up
    add_bb_to_compound(w, cpkeyboard, menu_key_color,
    Point3D( key_row * KEY_SPACING - 1*KEY_1_WIDTH, 7 * KEY_SPACING+ 7 * KEY_1_LENGTH + (3) * KEY_SPACING+ (3) * KEY_1_LENGTH, key_height),
    KEY_HALF_WIDTH, KEY_LENGTH + KEY_1_LENGTH, KEY_HEIGHT);

    //cover pad
    add_bb_to_compound(w, cpkeyboard, grey,Point3D(-2,-1,0),
    7 * KEY_SPACING - KEY_HALF_WIDTH, 14 * KEY_SPACING + KEY_HALF_LENGTH, KEY_1_HEIGHT);

    iskeyboard->rotate_z(-135);
    iskeyboard->translate(-35, -35, 35);
    //============================================================
    //3.Glossy Apple Pen
    Compound* cppen = new Compound();
    Instance* ispen = new Instance(cppen);
    //pen-body
    Instance* ispen_body = new Instance(new SolidCylinder(0, 10.5 * KEY_SPACING, 1.3 * KEY_1_WIDTH));
    w->set_material(ispen_body,white);
    cppen->add_object(ispen_body);
    //pen-head-curve
    Instance* ispen_head_curve = new Instance(new SolidCone(KEY_SPACING, 1.3 * KEY_1_WIDTH));
    w->set_material(ispen_head_curve, white);
    ispen_head_curve->rotate_x(180);
    cppen->add_object(ispen_head_curve);
    //pen-head-pin
    Instance* ispen_head_pin = new Instance(new SolidCone(KEY_SPACING, 1.0 * KEY_1_WIDTH));
    w->set_material(ispen_head_pin, grey);
    ispen_head_pin->rotate_x(180);
    ispen_head_pin->translate(0,-1.0,0);
    cppen->add_object(ispen_head_pin);
    //pen-body-liner
    Instance* ispen_body_liner = new Instance(new SolidCylinder(0,3,1.31*KEY_1_WIDTH));
    w->set_material(ispen_body_liner, grey);
    ispen_body_liner->translate(0, 9.3*KEY_SPACING, 0);
    cppen->add_object(ispen_body_liner);

    //pen-tail
    Instance* ispen_tail = new Instance(new Sphere(Point3D(0,10.5*KEY_SPACING,0), 1.3*KEY_1_WIDTH));
    w->set_material(ispen_tail, white);
    cppen->add_object(ispen_tail);

    ispen->rotate_z(-135);
    ispen->translate(-50, 10, 20);

    //============================================================
    //4.Transparent Glass cup
    Compound* cpglass = new Compound();
    Instance* isglass = new Instance(cpglass);
    //============================================================
    //5.Phong book
    Compound* cpbook = new Compound();
    Instance* isbook = new Instance(cpbook);
    //============================================================
    //6.Glossy (area light) lamp
    Compound* cplamp = new Compound();
    Instance* islamp = new Instance(cplamp);
    //============================================================
    //7.Matte table
    Compound* cptable = new Compound();
    Instance* istable = new Instance(cptable);
    cptable->add_object(iskeyboard); //done
    cptable->add_object(ispen); //done
    cptable->add_object(isglass);
    cptable->add_object(isbook);
    cptable->add_object(islamp);
    //============================================================
    //8.Matte chair
    Compound* cpchair = new Compound();
    Instance* ischair = new Instance(cpchair);
    //============================================================
    //9.Closing up
    w->add_object(istable);
    w->add_object(ischair);
}
