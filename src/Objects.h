class Human{
    public:
        bool atGround;
        bool lookingRight;
        int xPos;
        int yPos;
        int xVel;
        int yVel;

        Human(int x,int y, bool LR){
            xPos = x;
            yPos = y;
            lookingRight = LR;
        }
};