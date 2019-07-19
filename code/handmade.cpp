#include "handmade.h"

internal void
GameOutputSound(game_state *GameState, game_sound_output_buffer *SoundBuffer, int ToneHz)
{
  int16 ToneVolume = 3000;
  int WavePeriod = SoundBuffer->SamplesPerSecond / ToneHz;

  int16 *SampleOut = SoundBuffer->Samples;
  for (int SampleIndex = 0;
       SampleIndex < SoundBuffer->SampleCount;
       ++SampleIndex)
  {
    // TODO(casey): Draw this out for people
#if 0
    real32 SineValue = sinf(GameState->tSine);
    int16 SampleValue = (int16)(SineValue * ToneVolume);
#else
    int16 SampleValue = 0;
#endif
    *SampleOut++ = SampleValue;
    *SampleOut++ = SampleValue;
#if 0
    GameState->tSine += 2.0f * Pi32 * 1.0f / (real32)WavePeriod;
    if (GameState->tSine > 2.0f * Pi32)
    {
      GameState->tSine -= 2.0f * Pi32;
    }
#endif
  }
}

internal int32
RoundReal32ToInt32(real32 Real32)
{
  int32 Result = (int32)(Real32 + 0.5f);
  return (Result);
}

internal void
DrawRectangle(game_offscreen_buffer *Buffer,
              real32 RealMinX, real32 RealMinY, real32 RealMaxX, real32 RealMaxY)
{

  int MinX = RoundReal32ToInt32(RealMinX);
  int MinY = RoundReal32ToInt32(RealMinY);
  int MaxX = RoundReal32ToInt32(RealMaxX);
  int MaxY = RoundReal32ToInt32(RealMaxY);

  uint8 *EndOfBuffer = (uint8 *)Buffer->Memory + Buffer->Pitch * Buffer->Height;

  uint32 Color = 0xFFFFFFFF;
  int Top = MinY;
  int Bottom = MaxY;
  for (int X = MinX;
       X < MaxX;
       ++X)
  {
    uint8 *Pixel = ((uint8 *)Buffer->Memory +
                    X * Buffer->BytesPerPixel +
                    Top * Buffer->Pitch);
    for (int Y = Top;
         Y < Bottom;
         ++Y)
    {
      if ((Pixel >= Buffer->Memory) &&
          ((Pixel + 3) <= EndOfBuffer))
      {
        *(uint32 *)Pixel = Color;
      }

      Pixel += Buffer->Pitch;
    }
  }
}

extern "C" GAME_UPDATE_AND_RENDER(GameUpdateAndRender)
{
  Assert((&Input->Controllers[0].Terminator - &Input->Controllers[0].Buttons[0]) ==
         (ArrayCount(Input->Controllers[0].Buttons)));
  Assert(sizeof(game_state) <= Memory->PermanentStorageSize);

  game_state *GameState = (game_state *)Memory->PermanentStorage;
  if (!Memory->IsInitialized)
  {
    Memory->IsInitialized = true;
  }

  for (int ControllerIndex = 0;
       ControllerIndex < ArrayCount(Input->Controllers);
       ++ControllerIndex)
  {
    game_controller_input *Controller = GetController(Input, ControllerIndex);
    if (Controller->IsAnalog)
    {
    }
    else
    {
    }
  }

  DrawRectangle(Buffer, 10, 10, 130, 30);
  // DrawRectangle(Buffer, Input->MouseX, Input->MouseY);
}

extern "C" GAME_GET_SOUND_SAMPLES(GameGetSoundSamples)
{
  game_state *GameState = (game_state *)Memory->PermanentStorage;
  GameOutputSound(GameState, SoundBuffer, 440);
}

/* 
internal void
RenderWeirdGradient(game_offscreen_buffer *Buffer, int BlueOffset, int GreenOffset)
{
  // TODO(casey): Let's see what the optimizer does

  uint8 *Row = (uint8 *)Buffer->Memory;
  for (int Y = 0;
       Y < Buffer->Height;
       ++Y)
  {
    uint32 *Pixel = (uint32 *)Row;
    for (int X = 0;
         X < Buffer->Width;
         ++X)
    {
      uint8 Blue = (uint8)(X + BlueOffset);
      uint8 Green = (uint8)(Y + GreenOffset);

      *Pixel++ = ((Green << 16) | Blue);
    }

    Row += Buffer->Pitch;
  }
}
*/