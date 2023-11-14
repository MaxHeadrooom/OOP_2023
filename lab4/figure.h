#pragma once

class Figure
{
    public:
        Figure() = default;
        virtual ~Figure() = default;

        // virtual pointer12 calculate_mid() const = 0;
        //double calculate_S() const = 0;

        virtual explicit operator double() const 
        {
            return 0.0;
        };

    protected:
};