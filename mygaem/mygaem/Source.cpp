#include <Jopnal/Jopnal.hpp>

#include "MyEventHandler.h"



class MyScene : public jop::Scene
{
private:
    jop::WeakReference<jop::Object> m_camera;
    jop::WeakReference<jop::Object> m_camParent;
    jop::WeakReference<jop::Object> m_object;
    jop::WeakReference<jop::Object> m_light;
    jop::WeakReference<jop::Object> m_light2;
    jop::WeakReference<jop::Object> m_lightParent2;
    jop::WeakReference<jop::Object> m_object2;
    jop::WeakReference<jop::Object> m_object3;
    jop::WeakReference<jop::Object> m_object4;
    jop::WeakReference<jop::Object> m_cubes[27];
    jop::WeakReference<jop::Object> m_base;
    jop::WeakReference<jop::Object> m_selectionLight;
    std::unique_ptr<Rubics> rubics;

public:

    MyScene()
        : jop::Scene("MyScene"),
        m_object(), m_light()
    {
        //Parent for camera (used in cam movement)
        m_camParent = createChild("camParent");
        //m_camParent->createComponent<jop::GenericDrawable>(getRenderer());
        m_camParent->setPosition(.0f, .0f, .0f);
        m_camParent->addTag("CamParent");
        //Camera
        m_camera = m_camParent->createChild("cam");
        m_camera->createComponent<jop::Camera>(getRenderer(), jop::Camera::Projection::Perspective);
        //m_camera->getComponent<jop::Camera>()->setFieldOfView(glm::half_pi<float>()); // FOV
        m_camera->setPosition(0.f, 0.f, 50.f);
        m_camera->addTag("Cam");

        m_base = createChild("BoxModel");
        jop::ModelLoader::Options ml;
        ml.collapseTree = false; // False to keep parent/child relations from blender scene
        m_base->createComponent < jop::ModelLoader>().load("expScene.obj", ml);
        m_base->setPosition(.0f, .0f, .0f);
        m_base->setScale(1.0f);

        rubics = std::make_unique<Rubics>(glm::vec3(.0f, .0f, .0f), 1.0f, m_base, getWorld());
        jop::Engine::getSubsystem<jop::Window>()->setEventHandler<MyEventHandler>(*rubics);
       
        m_object2 = createChild("empty");
        m_object2->setPosition(2.f, 2.f, 2.f);

        m_lightParent2 = createChild("empty");
        m_lightParent2->setPosition(2.f, 2.f, 2.f);
        //m_lightParent2->createComponent<jop::GenericDrawable>(getRenderer());

        /*m_selectionLight = createChild("selectionLight");
        m_selectionLight->setPosition(2.f, 2.f, 2.f);
        auto& mat = jop::ResourceManager::getEmptyResource<jop::Material>("Testi").setMap(jop::Material::Map::Diffuse, jop::Texture2D::getError());
        m_selectionLight->createComponent<jop::GenericDrawable>(getRenderer()).getModel().setMaterial(mat);
        m_selectionLight->createComponent<jop::LightSource>(getRenderer(), jop::LightSource::Type::Point);
        m_selectionLight->addTag("Selection");*/
        


        //Light object
        m_light = createChild("rotating light");
        m_light->createComponent<jop::LightSource>(getRenderer(), jop::LightSource::Type::Directional);
        
        //m_light->getComponent<jop::LightSource>()->setCutoff(1.5f, 1.75f);
        //m_light->getComponent<jop::LightSource>()->setRange(180.f);
        //m_light->createComponent<jop::GenericDrawable>(getRenderer()); //visualizer to see the lightobject
        //m_light->setParent(m_object2);
        //Light object
        //m_light2 = createChild("rotating light");
        //m_light2->createComponent<jop::LightSource>(getRenderer(), jop::LightSource::Type::Spot);
        //m_light2->setPosition(4.f, 0.f, 0.f);
        //m_light2->getComponent<jop::LightSource>()->setCutoff(2.5f, 3.f);
        ////m_light2->createComponent<jop::GenericDrawable>(getRenderer()); //visualizer to see the lightobject
        //m_light2->setParent(m_lightParent2);


        jop::Material::getDefault().setAttributeField(jop::Material::Attribute::DiffuseMap | jop::Material::Attribute::Phong);
        
        //Cube
        int offset = 2; //Cube offset from each other == cube size
        
        //for (size_t x = 0; x < 3; ++x)
        //{
        //    for (size_t y = 0; y < 3; ++y)
        //    {
        //        for (size_t z = 0; z < 3; ++z)
        //        {
        //            m_cubes[x + y * 3 + z * 9] = createChild("base");
        //            m_cubes[x + y * 3 + z * 9]->addTag("Rubix");
        //            //m_cubes[x + y * 3 + z * 9]->createComponent<jop::GenericDrawable>(getRenderer());
        //            m_cubes[x + y * 3 + z * 9]->createComponent<jop::ModelLoader>().load("testi.obj");
        //            m_cubes[x + y * 3 + z * 9]->setScale(10.f);
        //            m_cubes[x + y * 3 + z * 9]->setPosition(x * offset, y * offset, z * offset);
        //            m_cubes[x + y * 3 + z * 9]->createComponent<jop::RigidBody>(getWorld(), cInfo);
        //            auto drawable = m_cubes[x + y * 3 + z * 9]->getComponent<jop::GenericDrawable>();
        //        }
        //    }
        //}
        //m_cubes[0]->addTag("Rubix");
        
        
    }

    void preUpdate(const float deltaTime) override
    {
        //m_object3->setPosition(m_object3->getPosition().x * jop::Engine::getTotalTime(), m_object3->getPosition().y, m_object3->getPosition().z);   
    }
    void postUpdate(const float deltaTime) override
    {
        m_light->setPosition(m_camera->getGlobalPosition());
        m_light->lookAt(2.f, 2.f, 2.f);
        
        //m_light2->lookAt(2.f, 2.f, 2.f);
        glm::vec4 color(1.0f, (std::sin(jop::Engine::getTotalTime()) / 2) + 0.5, 0.6f, 1.0f);

        m_object2->rotate(0.f, -1.f * deltaTime, 0.f);
        m_lightParent2->rotate(0.f, 0.f,0.75f * deltaTime);
        //m_camParent->rotate(0.f, 0.f, 0.f);
        //m_light->getComponent<jop::LightSource>()->setIntensity(jop::Color(color.r, color.g, color.b, color.a));
        //m_light2->getComponent<jop::LightSource>()->setIntensity(jop::Color(color.r, color.g, color.b * 2.f, color.a));
    }
};

int main(int argc, char* argv[])
{
    JOP_ENGINE_INIT("MyProject", argc, argv);
    
    

    jop::Engine::createScene<MyScene>();

    //Rubics rubix(glm::vec3(2.f, 2.f, 2.f), 0.2f);

    return JOP_MAIN_LOOP;
}