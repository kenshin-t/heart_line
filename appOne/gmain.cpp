#include"libOne.h"
#define HEART_
#ifdef HEART_
void getShapePos(float t, float r, float& x, float& y) {
    x = pow(sin(t), 3) * r;
    y = (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t)) / 16 * r;
}
#else
void getShapePos(float t, float r, float& x, float& y) {
    x = sin(t) * r;
    y = cos(t) * r;
}
#endif
void gmain() {
    window(1920, 1080, full);
    float cx = width / 2;
    float cy = height / 2 + 50;
    float sx, sy, ex, ey;
    float radius = 200;
    float deg = 0, limmitDeg = 0, inc = 1;
    int cnt = 0;
    bool showFlag = true;
    angleMode(DEGREES);
    ShowCursor(FALSE);
    while (notQuit) {
        //アニメーション制御
        if (limmitDeg < 360) {
            limmitDeg += inc;
        }
        else {
            cnt++;
            if (cnt > 60) {
                cnt = 0;
                limmitDeg = 0;
            }
        }
        clear(25);
        //XY軸
        stroke(50);
        strokeWeight(2);
        line(cx - radius, cy, cx + radius, cy);
        line(cx, cy - radius, cx, cy + radius);
        //limmitDegまでハートのlineを描く
        deg = 0;
        getShapePos(deg, radius, sx, sy);//始点
        while (deg <= limmitDeg) {
            getShapePos(deg + inc, radius, ex, ey);//終点
            //ハートライン
            strokeWeight(20);
            stroke(255, 128, 255);
            line(cx + sx, cy - sy, cx + ex, cy - ey);
            //ｘ座標カーブ
            strokeWeight(4);
            stroke(255, 128, 128);
            line(cx + sx, deg, cx + ex, deg+inc);
            //ｙ座標カーブ
            stroke(128, 255, 128);
            line(cx/3 + deg, cy - sy, cx/3 + deg+inc, cy - ey);
            //終点を次のlineの始点にする
            sx = ex;
            sy = ey;
            deg += inc;
        }
        //x座標を下まで伸ばす
        strokeWeight(2);
        stroke(128);
        line(cx + sx, deg, cx + sx, height);
        //y座標を右まで伸ばす
        line(cx / 3 + deg, cy - sy, width, cy - sy);
#ifdef HEART_
        //式の表示
        if (isTrigger(KEY_SPACE))showFlag = !showFlag;
        if (showFlag) {
            fill(255);
            textSize(30);
            text("x = pow(sin(t), 3)", cx + radius, 180);
            text("y = ( 13*cos(t) - 5*cos(2*t) - 2*cos(3*t) - cos(4*t) ) / 16", 60, cy + radius + 100);
        }
#endif
    }
    ShowCursor(TRUE);
}