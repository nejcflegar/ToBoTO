class Human{
    public:
        bool atGround;
        bool lookingRight;
        int xPos;
        int yPos;
        int xVel;
        int yVel;
        int skinRotation = 0;

        Human(int x,int y, bool LR){
            xPos = x;
            yPos = y;
            lookingRight = LR;
        }
};

class Ground{
    public:
        int xPos;
        int yPos;
        int skinRotation = 0;

        Ground(int x, int y, int SR){
            xPos = x;
            yPos = y;
            skinRotation = SR;
        }
};