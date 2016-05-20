#ifndef RUBICS_H
#define RUBICS_H

#include <Jopnal/Jopnal.hpp>
#include "MyEventHandler.h"

struct Face
{

    jop::WeakReference<jop::Object> baseCube; // Middle cube - parent to other cubes

    //    C1 C2 C3
    // R1 X  X  X
    // R2 X  X  X
    // R3 X  X  X
    jop::WeakReference<jop::Object> row1[3];
    jop::WeakReference<jop::Object> row2[3];
    jop::WeakReference<jop::Object> row3[3];

    jop::WeakReference<jop::Object> col1[3];
    jop::WeakReference<jop::Object> col2[3];
    jop::WeakReference<jop::Object> col3[3];

    // Pointers to neighboring faces
    std::shared_ptr<Face> N; // North 
    std::shared_ptr<Face> W; // West
    std::shared_ptr<Face> E; // East
    std::shared_ptr<Face> S; // South

    glm::vec3 rotationVec;

    void init()
    {
        col1[0] = row1[0];
        col1[1] = row2[0];
        col1[2] = row3[0];

        col2[0] = row1[1];
        col2[1] = row2[1];
        col2[2] = row3[1];

        col3[0] = row1[2];
        col3[1] = row2[2];
        col3[2] = row3[2];      
    }
    void setParentActive()
    {
        for (size_t i = 0; i < 3; ++i)
        {
            row1[i]->setParent(baseCube);
            row3[i]->setParent(baseCube);
        }
        row2[0]->setParent(baseCube);
        row2[2]->setParent(baseCube);

    }

    void clearParent()
    {
        for (size_t i = 0; i < 3; ++i)
        {
            row1[i]->setParent(jop::Engine::getCurrentScene().getAsObject());
            row3[i]->setParent(jop::Engine::getCurrentScene().getAsObject());
        }
        row2[0]->setParent(jop::Engine::getCurrentScene().getAsObject());
        row2[2]->setParent(jop::Engine::getCurrentScene().getAsObject());
    }

};

class Rubics
{
protected:
    std::vector<jop::WeakReference<jop::Object>> cubes; // All cubes
    std::vector<Face> faces; // 6 Faces of the cube

    //std::shared_ptr<Face> face1;
    //std::shared_ptr<Face> face2;
    //std::shared_ptr<Face> face3;
    //std::shared_ptr<Face> face4;
    //std::shared_ptr<Face> face5;
    //std::shared_ptr<Face> face6;

public:
    Rubics(glm::vec3 position, float scale, jop::Object& obj, jop::World& world)
    {
        // Get all cubes
        for (int i = 1; i < 27; i++)
        {
            std::string s = std::to_string(i);
            cubes.emplace_back(obj.findChild(s, false, true));
        }

        // For picking purposes
        jop::RigidBody::ConstructInfo cInfo(jop::ResourceManager::getNamedResource<jop::BoxShape>("box", 50.0f), jop::RigidBody::Type::KinematicSensor, 1.0f);

        //Face face1; // top face
        // 9 8 7
        // 6 5 4
        // 3 2 1
        Face face1;
        std::string s = std::to_string(5); // mid cube id
        face1.baseCube = obj.createChild("face");
        face1.baseCube = obj.findChild(s);
        face1.baseCube->createComponent<jop::RigidBody>(world, cInfo);
        face1.baseCube->addTag("face");
        // 9 8 7
        face1.row1[0] = obj.createChild("face");
        face1.row1[0] = cubes[9 - 1];
        face1.row1[1] = obj.createChild("face");
        face1.row1[1] = cubes[8 - 1];
        face1.row1[2] = obj.createChild("face");
        face1.row1[2] = cubes[7 - 1];
        // 6 5 4
        face1.row2[0] = obj.createChild("face");
        face1.row2[0] = cubes[6 - 1];
        face1.row2[1] = obj.createChild("face");
        face1.row2[1] = cubes[5 - 1];
        face1.row2[2] = obj.createChild("face");
        face1.row2[2] = cubes[4 - 1];
        // 3 2 1
        face1.row3[0] = obj.createChild("face");
        face1.row3[0] = cubes[3 - 1];
        face1.row3[1] = obj.createChild("face");
        face1.row3[1] = cubes[2 - 1];
        face1.row3[2] = obj.createChild("face");
        face1.row3[2] = cubes[1 - 1];

        face1.rotationVec = face1.baseCube->getGlobalUp();
        face1.init();

        Face face2;
        //  9  6  3
        // 12 11 10
        // 20 19 18
        std::string s2 = std::to_string(11); // mid cube id
        face2.baseCube = obj.createChild("face");
        face2.baseCube = obj.findChild(s2);
        face2.baseCube->createComponent<jop::RigidBody>(world, cInfo);
        face2.baseCube->addTag("face");
        // 9 6 3
        face2.row1[0] = obj.createChild("face");
        face2.row1[0] = cubes[9 - 1];
        face2.row1[1] = obj.createChild("face");
        face2.row1[1] = cubes[6 - 1];
        face2.row1[2] = obj.createChild("face");
        face2.row1[2] = cubes[3 - 1];
        // 12 11 10
        face2.row2[0] = obj.createChild("face");
        face2.row2[0] = cubes[12 - 1];
        face2.row2[1] = obj.createChild("face");
        face2.row2[1] = cubes[11 - 1];
        face2.row2[2] = obj.createChild("face");
        face2.row2[2] = cubes[10 - 1];
        // 20 19 18
        face2.row3[0] = obj.createChild("face");
        face2.row3[0] = cubes[20 - 1];
        face2.row3[1] = obj.createChild("face");
        face2.row3[1] = cubes[19 - 1];
        face2.row3[2] = obj.createChild("face");
        face2.row3[2] = cubes[18 - 1];

        face2.rotationVec = face2.baseCube->getGlobalRight();
        face2.init();

        Face face3; // bottom face
        // 18 21 24
        // 19 22 25
        // 20 23 26
        std::string s3 = std::to_string(22); // mid cube id
        face3.baseCube = obj.createChild("face");
        face3.baseCube = obj.findChild(s3);
        face3.baseCube->createComponent<jop::RigidBody>(world, cInfo);
        face3.baseCube->addTag("face");
        // 18 21 24
        face3.row1[0] = obj.createChild("face");
        face3.row1[0] = cubes[18 - 1];
        face3.row1[1] = obj.createChild("face");
        face3.row1[1] = cubes[21 - 1];
        face3.row1[2] = obj.createChild("face");
        face3.row1[2] = cubes[24 - 1];
        // 19 22 25
        face3.row2[0] = obj.createChild("face");
        face3.row2[0] = cubes[19 - 1];
        face3.row2[1] = obj.createChild("face");
        face3.row2[1] = cubes[22 - 1];
        face3.row2[2] = obj.createChild("face");
        face3.row2[2] = cubes[25 - 1];
        // 20 23 26
        face3.row3[0] = obj.createChild("face");
        face3.row3[0] = cubes[20 - 1];
        face3.row3[1] = obj.createChild("face");
        face3.row3[1] = cubes[23 - 1];
        face3.row3[2] = obj.createChild("face");
        face3.row3[2] = cubes[26 - 1];

        face3.rotationVec = -face3.baseCube->getGlobalUp();
        face3.init();

        Face face4;
        //  1  4  7
        // 15 16 17
        // 24 25 26
        std::string s4 = std::to_string(16); // mid cube id
        face4.baseCube = obj.createChild("face");
        face4.baseCube = obj.findChild(s4);
        face4.baseCube->createComponent<jop::RigidBody>(world, cInfo);
        face4.baseCube->addTag("face");
        // 1 4 7
        face4.row1[0] = obj.createChild("face");
        face4.row1[0] = cubes[1 - 1];
        face4.row1[1] = obj.createChild("face");
        face4.row1[1] = cubes[4 - 1];
        face4.row1[2] = obj.createChild("face");
        face4.row1[2] = cubes[7 - 1];
        // 15 16 17
        face4.row2[0] = obj.createChild("face");
        face4.row2[0] = cubes[15 - 1];
        face4.row2[1] = obj.createChild("face");
        face4.row2[1] = cubes[16 - 1];
        face4.row2[2] = obj.createChild("face");
        face4.row2[2] = cubes[17 - 1];
        // 24 25 26
        face4.row3[0] = obj.createChild("face");
        face4.row3[0] = cubes[24 - 1];
        face4.row3[1] = obj.createChild("face");
        face4.row3[1] = cubes[25 - 1];
        face4.row3[2] = obj.createChild("face");
        face4.row3[2] = cubes[26 - 1];
        
        face4.rotationVec = -face4.baseCube->getGlobalRight();
        face4.init();

        Face face5;
        //  7  8  9
        // 17 14 12
        // 26 23 20
        std::string s5 = std::to_string(14); // mid cube id
        face5.baseCube = obj.createChild("face");
        face5.baseCube = obj.findChild(s5);
        face5.baseCube->createComponent<jop::RigidBody>(world, cInfo);
        face5.baseCube->addTag("face");
        // 7 8 9
        face5.row1[0] = obj.createChild("face");
        face5.row1[0] = cubes[7 - 1];
        face5.row1[1] = obj.createChild("face");
        face5.row1[1] = cubes[8 - 1];
        face5.row1[2] = obj.createChild("face");
        face5.row1[2] = cubes[9 - 1];
        // 17 14 12
        face5.row2[0] = obj.createChild("face");
        face5.row2[0] = cubes[17 - 1];
        face5.row2[1] = obj.createChild("face");
        face5.row2[1] = cubes[14 - 1];
        face5.row2[2] = obj.createChild("face");
        face5.row2[2] = cubes[12 - 1];
        // 26 23 20
        face5.row3[0] = obj.createChild("face");
        face5.row3[0] = cubes[26 - 1];
        face5.row3[1] = obj.createChild("face");
        face5.row3[1] = cubes[23 - 1];
        face5.row3[2] = obj.createChild("face");
        face5.row3[2] = cubes[20 - 1];

        face5.rotationVec = -face5.baseCube->getGlobalFront();
        face5.init();

        Face face6;
        // 3  2  1
        // 10 13 15
        // 18 21 24
        std::string s6 = std::to_string(13); // mid cube id
        face6.baseCube = obj.createChild("face");
        face6.baseCube = obj.findChild(s6);
        face6.baseCube->createComponent<jop::RigidBody>(world, cInfo);
        face6.baseCube->addTag("face");
        // 3 2 1
        face6.row1[0] = obj.createChild("face");
        face6.row1[0] = cubes[3 - 1];
        face6.row1[1] = obj.createChild("face");
        face6.row1[1] = cubes[2 - 1];
        face6.row1[2] = obj.createChild("face");
        face6.row1[2] = cubes[1 - 1];
        // 10 13 15
        face6.row2[0] = obj.createChild("face");
        face6.row2[0] = cubes[10 - 1];
        face6.row2[1] = obj.createChild("face");
        face6.row2[1] = cubes[13 - 1];
        face6.row2[2] = obj.createChild("face");
        face6.row2[2] = cubes[15 - 1];
        // 18 21 24
        face6.row3[0] = obj.createChild("face");
        face6.row3[0] = cubes[18 - 1];
        face6.row3[1] = obj.createChild("face");
        face6.row3[1] = cubes[21 - 1];
        face6.row3[2] = obj.createChild("face");
        face6.row3[2] = cubes[24 - 1];

        face6.rotationVec = face6.baseCube->getGlobalFront();
        face6.init();
        
        // Set neighbor relations
        // 1 = orange 5
        // 2 = red 11
        // 3 = blue 22
        // 4 = yellow 16
        // 5 = green 14
        // 6 = white 13

        face1.N = std::make_shared<Face>(face5);
        face1.S = std::make_shared<Face>(face6);
        face1.W = std::make_shared<Face>(face2);
        face1.E = std::make_shared<Face>(face4);

        face2.N = std::make_shared<Face>(face1);
        face2.S = std::make_shared<Face>(face3);
        face2.W = std::make_shared<Face>(face5);
        face2.E = std::make_shared<Face>(face6);

        face3.N = std::make_shared<Face>(face5);
        face3.S = std::make_shared<Face>(face6);
        face3.W = std::make_shared<Face>(face2);
        face3.E = std::make_shared<Face>(face4);

        face4.N = std::make_shared<Face>(face1);
        face4.S = std::make_shared<Face>(face3);
        face4.W = std::make_shared<Face>(face6);
        face4.E = std::make_shared<Face>(face5);

        face5.N = std::make_shared<Face>(face1);
        face5.S = std::make_shared<Face>(face3);
        face5.W = std::make_shared<Face>(face2);
        face5.E = std::make_shared<Face>(face4);

        face6.N = std::make_shared<Face>(face1);
        face6.S = std::make_shared<Face>(face3);
        face6.W = std::make_shared<Face>(face4);
        face6.E = std::make_shared<Face>(face2);


        faces.emplace_back(face1);
        faces.emplace_back(face2);
        faces.emplace_back(face3);
        faces.emplace_back(face4);
        faces.emplace_back(face5);
        faces.emplace_back(face6);

    };
    ~Rubics(){}

    void updateRelationsX(Face& face)
    {
        jop::WeakReference<jop::Object> oldN[3];
        jop::WeakReference<jop::Object> oldW[3];
        jop::WeakReference<jop::Object> oldE[3];
        jop::WeakReference<jop::Object> oldS[3];

        for (size_t i = 0; i < 3; ++i)
        {
            oldN[i] = face.row1[i];
            oldW[i] = face.col1[i];
            oldE[i] = face.col3[i];
            oldS[i] = face.row3[i];
        }

        std::string top = std::to_string(5); // mid cube id
        std::string bottom = std::to_string(22);
        std::string front = std::to_string(13);
        std::string behind = std::to_string(14);
        std::string right = std::to_string(16);
        std::string left = std::to_string(1);


        if (face.baseCube->getID() == top)
        {
            // For top:
            for (size_t i = 0; i < 3; ++i)
            {
                face.S->row1[i] = oldW[i];
                face.W->row1[i] = oldN[i];
                face.E->row1[i] = oldS[i];
                face.N->row1[i] = oldE[i];
            }
        }
        else if (face.baseCube->getID() == bottom)
        {
            // For bottom:
            for (size_t i = 0; i < 3; ++i)
            {
                face.N->row3[i] = oldW[i];
                face.W->row3[i] = oldS[i];
                face.E->row3[i] = oldN[i];
                face.S->row3[i] = oldE[i];
            }
        }
        else if ((face.baseCube->getID() == front))
        {
            // For front:
            for (size_t i = 0; i < 3; ++i)
            {
                face.N->row3[i] = oldW[i];
                face.W->col3[i] = oldS[i];
                face.E->col1[i] = oldN[i];
                face.S->row1[i] = oldE[i];
            }
        }
        else if ((face.baseCube->getID() == behind))
        {
            // For rear:
            for (size_t i = 0; i < 3; ++i)
            {
                face.N->row1[i] = oldW[i];
                face.W->col3[i] = oldS[i];
                face.E->col1[i] = oldN[i];
                face.S->row3[i] = oldE[i];
            }
        }
        else if ((face.baseCube->getID() == right))
        {
            // For right:
            for (size_t i = 0; i < 3; ++i)
            {
                face.N->col3[i] = oldW[i];
                face.W->col3[i] = oldS[i];
                face.E->col1[i] = oldN[i];
                face.S->col3[i] = oldE[i];
            }
        }
        else if ((face.baseCube->getID() == left))
        {
            // For left:
            for (size_t i = 0; i < 3; ++i)
            {
                face.N->col1[i] = oldW[i];
                face.W->col3[i] = oldS[i];
                face.E->col1[i] = oldN[i];
                face.S->col1[i] = oldE[i];
            }
        }
    }

    void moveClockwise(jop::WeakReference<jop::Object> obj)
    {
        
        for (size_t i = 0; i < faces.size(); ++i)
        {
            // Clear parent relations from other faces

            // Check which face we are on
            if (faces[i].baseCube->getID() == obj->getID())
            {
                // Set parent
                faces[i].setParentActive();
                // Do rotation

                faces[i].baseCube->rotate(glm::radians(90.f), faces[i].rotationVec);

                // Update neighbors
                updateRelationsX(faces[i]);
            }
            
           
        }
    }
    void moveY()
    {
        // Do movement (rotation)

        // Rotate  : Update all neighbor faces

        // new N row3 = old E col1
        // new E col1 = old S row1
        // new S row1 = old W col3
        // new W col3 = old N row3
    }
    void moveZ()
    {
        //RotateY/X 2 neighbor faces (W+E or N+S)
    }
    void updatePlanes()
    {
        // Update cubes on correct planes after doing a move
    }

    void scramble()
    {
        // To random movement to scramble the cube
    }



};


#endif