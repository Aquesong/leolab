#ifndef __LEOLAB_BOUNDARYAWAREMOBILITYCANVASVISUALIZER_H
#define __LEOLAB_BOUNDARYAWAREMOBILITYCANVASVISUALIZER_H

#include "inet/visualizer/canvas/mobility/MobilityCanvasVisualizer.h"

namespace leolab {

class BoundaryAwareMobilityCanvasVisualizer : public inet::visualizer::MobilityCanvasVisualizer
{
  protected:
    double boundaryJumpThreshold = 0.5;

  protected:
    virtual void initialize(int stage) override;
    virtual void extendMovementTrail(const inet::IMobility *mobility, inet::TrailFigure *trailFigure, omnetpp::cFigure::Point position) const override;
    virtual void addTrailResetPoint(const inet::IMobility *mobility, inet::TrailFigure *trailFigure, const omnetpp::cFigure::Point& position) const;
};

} // namespace leolab

#endif
