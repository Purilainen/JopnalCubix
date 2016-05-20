#ifndef MYEVENTHANDLER_H
#define MYEVENTHANDLER_H

#include <Jopnal/Jopnal.hpp>
#include "Rubics.h"

class MyEventHandler : public jop::WindowEventHandler
{
private:
    jop::WeakReference<jop::Object> m_obj;
    Rubics& r;
    float lastX, lastY;
public:
    MyEventHandler(jop::Window& w, Rubics& rubics) : jop::WindowEventHandler(w), r(rubics)
    {
    }

    void closed() override
    {
        jop::Engine::exit();
    }

    void keyPressed(const int key, int, int) override
    {
        if (key == jop::Keyboard::Escape)
            closed();
        if (key == jop::Keyboard::Left)
        {
            //jop::broadcast("[Ob(activeFace)] rotate 0 0.261799388 0");
                

        }
        if (key == jop::Keyboard::Right)
        {
            r.moveClockwise(m_obj);
        }
        if (key == jop::Keyboard::Up)
        {

        }
        if (key == jop::Keyboard::Down)
        {
        }
    }



    void mouseMoved(const float x, const float y) override
    {
        if (mouseButtonDown(jop::Mouse::Middle))
        {
            if (lastY < y)
            {
                //Nyökkäys eteenpäin  +pitch
                jop::broadcast("[Ob(CamParent)] rotate 0.08 0 0");
            }
            else if (lastY > y)
            {
                //Nyökkäys taaksepäin  -pitch
                jop::broadcast("[Ob(CamParent)] rotate -0.08 0 0");
            }
            else if (lastX < x)
            {
                //Kierto oikealle  +yaw
                jop::broadcast("[Ob(CamParent)] rotate 0 0.12 0");
            }
            else if (lastX > x)
            {
                //Kierto vasemmalle  -yaw
                jop::broadcast("[Ob(CamParent)] rotate 0 -0.12 0");
            }
            lastX = x;
            lastY = y;
        }
    }

    void mouseButtonPressed(const int button, const int) override
    {
        if (button == jop::Mouse::Middle)
        {
            //jop::broadcast("[Ob(CamParent)] rotate /*something something*/");
        }
        else if (button == jop::Mouse::Left)
        {
            //Cursor positions
            glm::vec2 cursorPos(getCursorPosition().x, getCursorPosition().y);
            //Get camera obj
            auto camera = jop::Engine::getCurrentScene().findChildrenWithTag("Cam", true)[0];
            //Get ray
            auto ray = camera->getComponent<jop::Camera>()->getPickRay(cursorPos, *jop::Engine::getSubsystem<jop::Window>());
            //Create ray pointer and scale it (999x)
            auto rayPtr = jop::Engine::getCurrentScene().getWorld().checkRayClosest(camera->getGlobalPosition(), ray * 999.f);
            if (rayPtr.collider)
            {
                //Get object
                auto obj = rayPtr.collider->getObject();
                if (/*obj->getID() == "sidecube"
                    */obj->hasTag("face"))
                {
                    //glm::vec3 pos = obj->getGlobalPosition();
                    //jop::broadcast("[Ob(Selection)] setPosition " + std::to_string(pos.x) + " " + std::to_string(pos.y) + " " + std::to_string(pos.z));


                    JOP_DEBUG_INFO(obj->getID());

                    auto temp = jop::Engine::getCurrentScene().findChildrenWithTag("activeFace", true);
                    for (auto& i : temp)
                    {
                        i->removeTag("activeFace");
                        
                    }
                    
                    // Get face - set tag as "ActiveFace"
                    m_obj = obj;
                    // TODO: Clear activeFace from previous picked object
                    obj->addTag("activeFace");
                }
            }


            //Move selection light on top of selected object
            //jop::broadcast selectionLight move objPos x y z
        }
        else if (button == jop::Mouse::Right)
        {
            //Deselect object
            //Move selection light to 2.f 2.f 2.f (origin)
        }

    }

    void mouseScrolled(const float x, const float y) override
    {
        if (y > 0)
            jop::broadcast("[Ob(Cam)] move 0 0 3");
        else if (y <= 0)
            jop::broadcast("[Ob(Cam)] move 0 0 -3");
    }


    
};

#endif