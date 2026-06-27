#pragma once
#include"core.h"
#include"ecs/component.h"
#include"math/matrix.h"

namespace nova{
    namespace physics{
        inline nova::mat3 CalculateTransform(
            float& delta,
            VelocityComponent& c_velocity,
            AccelarationComponent& c_accelaration,
            ForceComponent& c_force,
            MassComponent& c_mass
        ) 
        {
            nova::vec3 forceVector = (c_mass.mass == 0) ? nova::vec3{0,0,1} : nova::vec3{c_force.force.a/c_mass.mass,c_force.force.b/c_mass.mass,1};  
            nova::mat3 forceMatrix(
                1,0, forceVector.a,
                0,1, forceVector.b,
                0,0, 1
            );
            nova::vec3 accVector{c_accelaration.acc.a,c_accelaration.acc.b,1};
            accVector = forceMatrix*accVector;
            c_accelaration.acc.a = accVector.a;
            c_accelaration.acc.b = accVector.b;

            nova::mat3 accMatrix(
                1,0, accVector.a,
                0,1, accVector.b,
                0,0, 1
            );
            nova::vec3 velocityVector(c_velocity.velocity.a,c_velocity.velocity.b,1);
            velocityVector = accMatrix*velocityVector;
            c_velocity.velocity.a = velocityVector.a;
            c_velocity.velocity.b = velocityVector.b;

            return {
                1,0, velocityVector.a*delta,
                0,1, velocityVector.b*delta,
                0,1, 1
            };
        }

        inline nova::mat3 CalculateTransform(
            float& delta,
            VelocityComponent& c_velocity,
            AccelarationComponent& c_accelaration
        ){
            nova::mat3 accMatrix(
                1,0, c_accelaration.acc.a,
                0,1, c_accelaration.acc.b,
                0,0, 1
            );
            nova::vec3 velocityVector(c_velocity.velocity.a,c_velocity.velocity.b,1);
            velocityVector = accMatrix*velocityVector;
            c_velocity.velocity.a = velocityVector.a;
            c_velocity.velocity.b = velocityVector.b;

            return {
                1,0, velocityVector.a*delta,
                0,1, velocityVector.b*delta,
                0,1, 1
            };
        }

        inline nova::mat3 CalculateTransform(
            float& delta,
            VelocityComponent& c_velocity
        ){
            return{
                1,0, c_velocity.velocity.a*delta,
                0,1, c_velocity.velocity.b*delta,
                0,0, 1
            };
        }
    }
}