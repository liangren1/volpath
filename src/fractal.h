#ifndef fractal_h__
#define fractal_h__

class FractalJuliaSet
{
    float radius;
    float c[4];
    int maxIter;

    static void setFloat4(float v[4], float a, float b, float c, float d)
    {
        v[0] = a;
        v[1] = b;
        v[2] = c;
        v[3] = d;
    }

    static void quatSq(float q[4])
    {
        float r0;

        vec3 q_yzw(q[1], q[2], q[3]);

        r0 = q[0] * q[0] - dot(q_yzw, q_yzw);
        vec3 r_yzw(q_yzw*(q[0] * 2));

        q[0] = r0;
        q[1] = r_yzw.x;
        q[2] = r_yzw.y;
        q[3] = r_yzw.z;
    }

    static void add(float a[4], float b[4]){
        a[0] += b[0];
        a[1] += b[1];
        a[2] += b[2];
        a[3] += b[3];
    }
    static float length2(float a[4]){
        return a[0] * a[0] +
            a[1] * a[1] +
            a[2] * a[2] +
            a[3] * a[3];
    }
    static float eval_fractal(const vec3& pos, float radius, float c[4], int maxIter){

        float q[4] = { pos.x*radius, pos.y*radius, pos.z*radius, 0 };

        int iter = 0;
        do
        {
            quatSq(q);
            add(q, c);
        } while (length2(q) < 10.0f && iter++ < maxIter);

        //     return iter * (iter>5);
        //     return iter / float(maxIter);
        //     return log((float)iter+1) / log((float)maxIter);
        return (iter > maxIter * 0.9);
    }

public:
    float density(const vec3& pos)
    {
        return eval_fractal(pos, radius, c, maxIter);
    }

    FractalJuliaSet()
    {
        radius = 3.0f;
        //     setFloat4(c, -1, 0.2, 0, 0);
        //     setFloat4(c, -0.291,-0.399,0.339,0.437);
        //     setFloat4(c, -0.2,0.4,-0.4,-0.4);
        //     setFloat4(c, -0.213,-0.0410,-0.563,-0.560);
        //     setFloat4(c, -0.2,0.6,0.2,0.2);
        //     setFloat4(c, -0.162,0.163,0.560,-0.599);
        setFloat4(c, -0.2f, 0.8f, 0.0f, 0.0f);
        //     setFloat4(c, -0.445,0.339,-0.0889,-0.562);
        //     setFloat4(c, 0.185,0.478,0.125,-0.392);
        //     setFloat4(c, -0.450,-0.447,0.181,0.306);
        //     setFloat4(c, -0.218,-0.113,-0.181,-0.496);
        //     setFloat4(c, -0.137,-0.630,-0.475,-0.046);
        //     setFloat4(c, -0.125,-0.256,0.847,0.0895);

        //     maxIter = 20;
        maxIter = 30;
    }
};

#endif // fractal_h__
