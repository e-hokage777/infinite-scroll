To make a reusable 2D sprite-frame animation system in OpenGL, your architecture needs to split into three clean parts:
1. TextureAtlas: Holds the texture data and a grid or list of texture coordinates (UVs).
2. SpriteAnimation: A data asset container holding the frame list, timing, and duration.
3. SpriteAnimator: The lightweight component engine tracking individual playback states (time, frame index, loop settings).
This architecture allows you to share one SpriteAnimation data asset across hundreds of different enemies or players, each running their own independent SpriteAnimator.

1. The Data Assets (Decoupled from OpenGL)

First, define a single frame and a reusable animation sequence. A frame stores the UV coordinates (where it sits on the texture atlas) and how long it should display.
cpp
#pragma once
#include <vector>
#include <glm/glm.hpp>

struct SpriteFrame {
    glm::vec2 uvTopLeft;
    glm::vec2 uvBottomRight;
    float duration; // How long this frame lasts in seconds
};

struct SpriteAnimation {
    std::string name;
    std::vector<SpriteFrame> frames;
    bool isLooping = true;

    float GetTotalDuration() const {
        float total = 0.0f;
        for (const auto& frame : frames) total += frame.duration;
        return total;
    }
};
Use code with caution.

2. The Reusable SpriteAnimator Class

The animator class does not touch OpenGL rendering states. It only advances time and updates the current UV offsets.
cpp
#pragma once
#include "SpriteAnimation.h"

class SpriteAnimator {
public:
    SpriteAnimator() = default;

    void Play(const SpriteAnimation* animation) {
        m_CurrentAnimation = animation;
        m_CurrentTime = 0.0f;
        m_CurrentFrameIndex = 0;
    }

    void Update(float deltaTime) {
        if (!m_CurrentAnimation || m_CurrentAnimation->frames.empty()) return;

        m_CurrentTime += deltaTime * m_PlaybackSpeed;
        
        // Loop or clamp overall animation time
        float totalDuration = m_CurrentAnimation->GetTotalDuration();
        if (m_CurrentTime >= totalDuration) {
            if (m_CurrentAnimation->isLooping) {
                m_CurrentTime = fmod(m_CurrentTime, totalDuration);
                m_CurrentFrameIndex = 0; // Reset index to recalculate safely
            } else {
                m_CurrentTime = totalDuration;
                m_CurrentFrameIndex = m_CurrentAnimation->frames.size() - 1;
                return;
            }
        }

        // Advance through frames sequentially based on current elapsed time
        float accumulatedTime = 0.0f;
        for (size_t i = 0; i < m_CurrentAnimation->frames.size(); ++i) {
            accumulatedTime += m_CurrentAnimation->frames[i].duration;
            if (m_CurrentTime <= accumulatedTime) {
                m_CurrentFrameIndex = i;
                break;
            }
        }
    }

    // Getters for the Renderer
    const SpriteFrame& GetCurrentFrame() const {
        return m_CurrentAnimation->frames[m_CurrentFrameIndex];
    }

    void SetPlaybackSpeed(float speed) { m_PlaybackSpeed = speed; }

private:
    const SpriteAnimation* m_CurrentAnimation = nullptr;
    float m_CurrentTime = 0.0f;
    float m_PlaybackSpeed = 1.0f;
    size_t m_CurrentFrameIndex = 0;
};
Use code with caution.

3. Rendering the Animation in OpenGL

To feed this data into OpenGL efficiently without modifying your VBO vertex data dynamically every frame, pass the current frame's UV coordinates to your GLSL shader via uniforms.

The Vertex Shader (sprite.vert)

glsl
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords; // Base quad mapping (0.0 to 1.0)

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

// Pass the active frame's UV bounds from your Animator
uniform vec2 uvTopLeft;
uniform vec2 uvBottomRight;

void main() {
    gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
    
    // Map standard 0-1 quad coordinates to your texture atlas section
    TexCoords = mix(uvTopLeft, uvBottomRight, aTexCoords);
}
Use code with caution.

The Game Engine Loop Integration

When drawing, pull the current state from the animator and upload it straight to your shader program:
cpp
// Update Phase
playerAnimator.Update(deltaTime);
enemyAnimator.Update(deltaTime); // Runs independently!

// Render Phase
shader.Use();
glBindTexture(GL_TEXTURE_2D, textureAtlasID);

// Draw Player
const SpriteFrame& playerFrame = playerAnimator.GetCurrentFrame();
shader.SetVec2("uvTopLeft", playerFrame.uvTopLeft);
shader.SetVec2("uvBottomRight", playerFrame.uvBottomRight);
shader.SetMat4("model", playerModelMatrix);
playerQuad.Draw();

// Draw Enemy
const SpriteFrame& enemyFrame = enemyAnimator.GetCurrentFrame();
shader.SetVec2("uvTopLeft", enemyFrame.uvTopLeft);
shader.SetVec2("uvBottomRight", enemyFrame.uvBottomRight);
shader.SetMat4("model", enemyModelMatrix);
enemyQuad.Draw();
Use code with caution.

Why this design works perfectly:

• Batching Friendly: Because your vertices don't change and you use raw uniform vectors, you can easily adapt this to an Instanced Rendering layout later if you want to render thousands of animated sprites simultaneously.
• Flexibility: Individual frames can have completely variable durations (e.g., frame 1 lasts 0.1s, but frame 2 delays for 0.5s).
Do you already have a texture atlas layout parser (like a JSON loader for TexturePacker), or would you like a quick helper function to programmatically split a grid-based sprite sheet (e.g., a uniform 4x4 grid) into these SpriteFrame bounds?
