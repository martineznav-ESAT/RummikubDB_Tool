// @author Jonathan Martínez Navarro

#ifndef ScreenModules_H
#define ScreenModules_H

namespace ScreenModules{

    enum S_Module{
        TABLES,
        CUSTOM_QUERYS,
        QUERY_CONTENT,
        // BANG_SMALL,
        // BEAT_1,
        // BEAT_2,
        // EXTRA_SHIP,
        // FIRE,
        // UFO_BIG,
        // UFO_SMALL,
        // THRUST,
        TOTAL_S_MODULES
    };

    void Init();

    void DrawScreenModule(S_Module module);

    void EmptyMemory();
}

#endif