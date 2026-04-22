package leolab.visualizer.canvas.mobility;

import inet.visualizer.canvas.mobility.MobilityCanvasVisualizer;

simple BoundaryAwareMobilityCanvasVisualizer extends MobilityCanvasVisualizer
{
    parameters:
        double boundaryJumpThreshold = default(0.5); // Relative jump threshold against constraint area width/height
        @class(leolab::BoundaryAwareMobilityCanvasVisualizer);
}
