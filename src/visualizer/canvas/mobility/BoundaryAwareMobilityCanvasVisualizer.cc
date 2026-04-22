#include "BoundaryAwareMobilityCanvasVisualizer.h"

#include <cmath>

namespace leolab {

Define_Module(BoundaryAwareMobilityCanvasVisualizer);

using namespace omnetpp;
using namespace inet;
using namespace inet::visualizer;

void BoundaryAwareMobilityCanvasVisualizer::initialize(int stage)
{
    MobilityCanvasVisualizer::initialize(stage);
    if (stage == INITSTAGE_LOCAL)
        boundaryJumpThreshold = par("boundaryJumpThreshold");
}

void BoundaryAwareMobilityCanvasVisualizer::extendMovementTrail(const IMobility *mobility, TrailFigure *trailFigure, cFigure::Point position) const
{
    if (trailFigure->getNumFigures() > 0 && boundaryJumpThreshold > 0) {
        auto lastLine = check_and_cast<cLineFigure *>(trailFigure->getFigure(trailFigure->getNumFigures() - 1));
        auto previousPosition = lastLine->getEnd();
        auto dx = previousPosition.x - position.x;
        auto dy = previousPosition.y - position.y;

        auto areaMin = canvasProjection->computeCanvasPoint(mobility->getConstraintAreaMin());
        auto areaMax = canvasProjection->computeCanvasPoint(mobility->getConstraintAreaMax());
        auto width = std::abs(areaMax.x - areaMin.x);
        auto height = std::abs(areaMax.y - areaMin.y);

        bool boundaryJump =
            (width > 0 && std::abs(dx) > width * boundaryJumpThreshold) ||
            (height > 0 && std::abs(dy) > height * boundaryJumpThreshold);

        if (boundaryJump) {
            addTrailResetPoint(mobility, trailFigure, position);
            return;
        }
    }

    MobilityCanvasVisualizer::extendMovementTrail(mobility, trailFigure, position);
}

void BoundaryAwareMobilityCanvasVisualizer::addTrailResetPoint(const IMobility *mobility, TrailFigure *trailFigure, const cFigure::Point& position) const
{
    auto movementLine = new cLineFigure("movementTrail");
    movementLine->setTags((std::string("movement_trail recent_history ") + tags).c_str());
    movementLine->setTooltip("This point breaks a boundary-crossing movement trail segment");
    movementLine->setStart(position);
    movementLine->setEnd(position);
    auto module = const_cast<cModule *>(check_and_cast<const cModule *>(mobility));
    movementLine->setLineColor(movementTrailLineColorSet.getColor(module->getId()));
    movementLine->setLineStyle(movementTrailLineStyle);
    movementLine->setLineWidth(movementTrailLineWidth);
    movementLine->setZoomLineWidth(false);
    trailFigure->addFigure(movementLine);
}

} // namespace leolab
