#include "raymarcher.hh"


int main() {
    int width = 1600;
    int height = 900;
    
    int samplesPerPixel = 1;
    int numThreads = 8;

    std::shared_ptr<Natural> rouge = std::make_shared<Natural>(Color(1.0, 0.0, 0.0));
    std::shared_ptr<Natural> vert = std::make_shared<Natural>(Color(0.0, 1.0, 0.0));
    std::shared_ptr<Natural> rose = std::make_shared<Natural>(Color(0.5, 0.0, 0.5));
    std::shared_ptr<Natural> blanc = std::make_shared<Natural>(Color(1.0, 1.0, 1.0));

    std::shared_ptr<Reflect> refl = std::make_shared<Reflect>(Color(1.0, 1.0, 1.0));

    std::shared_ptr<Metal> iron = std::make_shared<Metal>(Color(1.0, 0.0, 1.0), 1.0);

    std::vector<std::vector<Color>> pixels(width, std::vector<Color>(height));
    Image im(width, height, pixels);

    Scene scene;
    const double h = 20.0;


    //! LUMIERES

    scene.lights.push_back(std::make_shared<Light>(Point3(0.0, -100.0, 0.0), Color(1.0, 1.0, 1.0)));
    // scene.lights.push_back(std::make_shared<Light>(Point3(50.0, -100.0, 0.0), Color(1.0, 0.0, 0.0)));
    // scene.lights.push_back(std::make_shared<Light>(Point3(-50.0, -100.0, 0.0), Color(0.0, 0.0, 1.0)));


    //! OBJETS

    scene.world.add(std::make_shared<Plane>(Vector3(0.0, -1.0, 0.0), -40.0, refl));    // Plan du sol
    // scene.world.add(std::make_shared<Plane>(Vector3(0.0, 0.0, 1.0), -90.0, blanc));     // Plan du fond


    scene.world.add(std::make_shared<Sphere>(Point3(15.0, h, -70.0), 20.0, rouge));         // Grosse
    scene.world.add(std::make_shared<Sphere>(Point3(-15.0, h - 20.0, -70.0), 10.0, vert)); // Petite

    Camera cam;

    render(cam, scene, im, samplesPerPixel, numThreads);

    im.savePPM("image_cree.ppm");
}
