/*
 * Flowerpot framework
 * Copyright (C) Jani Salo 2015. All rights reserved.
 */

#ifndef FLOWERPOT_DISPLAYATTRIBUTES_HPP
#define FLOWERPOT_DISPLAYATTRIBUTES_HPP

namespace flowerpot {
    class GLAttributes {
        public:
            GLAttributes(
                const int redBits      = 0,
                const int greenBits    = 0,
                const int blueBits     = 0,
                const int alphaBits    = 0,
                const int depthBits    = 0,
                const int stencilBits  = 0,
                const int contextMajor = 0,
                const int contextMinor = 0
            );

            int getRedBits() const;
            int getGreenBits() const;
            int getBlueBits() const;
            int getAlphaBits() const;
            int getStencilBits() const;
            int getDepthBits() const;
            
            int getContextMajor() const;
            int getContextMinor() const;

        private:
            int _redBits;
            int _greenBits;
            int _blueBits;
            int _alphaBits;
            int _depthBits;
            int _stencilBits;
            
            int _contextMajor;
            int _contextMinor;
    };

    inline GLAttributes::GLAttributes(
        const int redBits,
        const int greenBits,
        const int blueBits,
        const int alphaBits,
        const int depthBits,
        const int stencilBits,
        const int contextMajor,
        const int contextMinor
    ) :
        _redBits     (redBits),
        _greenBits   (greenBits),
        _blueBits    (blueBits),
        _alphaBits   (alphaBits),
        _depthBits   (depthBits),
        _stencilBits (stencilBits),
        _contextMajor(contextMajor),
        _contextMinor(contextMinor)
    {}

    inline int GLAttributes::getRedBits() const { 
        return _redBits; 
    }
    
    inline int GLAttributes::getGreenBits() const { 
        return _greenBits; 
    }
    
    inline int GLAttributes::getBlueBits() const { 
        return _blueBits; 
    }
    
    inline int GLAttributes::getAlphaBits() const { 
        return _alphaBits; 
    }
    
    inline int GLAttributes::getStencilBits() const { 
        return _stencilBits; 
    }
    
    inline int GLAttributes::getDepthBits() const { 
        return _depthBits; 
    }
    
    inline int GLAttributes::getContextMajor() const { 
        return _contextMajor; 
    }
    
    inline int GLAttributes::getContextMinor() const { 
        return _contextMinor; 
    }
};

#endif /* FLOWERPOT_DISPLAYATTRIBUTES_HPP */

