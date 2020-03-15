#include <mbgl/gl/custom_layer.hpp>
#include <mbgl/gl/custom_layer_impl.hpp>
#include <mbgl/gl/render_custom_layer.hpp>
#include <mbgl/style/layer_observer.hpp>

namespace mbgl {
namespace style {

namespace {
const LayerTypeInfo typeInfoCustom{"",
                                   LayerTypeInfo::Source::NotRequired,
                                   LayerTypeInfo::Pass3D::NotRequired,
                                   LayerTypeInfo::Layout::NotRequired,
                                   LayerTypeInfo::FadingTiles::NotRequired,
                                   LayerTypeInfo::CrossTileIndex::NotRequired,
                                   LayerTypeInfo::TileKind::NotRequired};
}  // namespace

CustomLayer::CustomLayer(const std::string& layerID,
                         std::unique_ptr<CustomLayerHost> host)
    : Layer(makeMutable<Impl>(layerID, std::move(host))) {
}

CustomLayer::~CustomLayer() = default;

const CustomLayer::Impl& CustomLayer::impl() const {
    return static_cast<const Impl&>(*baseImpl);
}

Mutable<CustomLayer::Impl> CustomLayer::mutableImpl() const {
    return makeMutable<Impl>(impl());
}

std::unique_ptr<Layer> CustomLayer::cloneRef(const std::string&) const {
    assert(false);
    return nullptr;
}

using namespace conversion;

optional<Error> CustomLayer::setProperty(const std::string&, const Convertible&) {
    return Error { "layer doesn't support this property" };
}

StyleProperty CustomLayer::getProperty(const std::string&) const {
    return {};
}

Mutable<Layer::Impl> CustomLayer::mutableBaseImpl() const {
    return staticMutableCast<Layer::Impl>(mutableImpl());
}

// static
const LayerTypeInfo* CustomLayer::Impl::staticTypeInfo() noexcept {
    return &typeInfoCustom;
}

bool CustomLayerRenderParameters::operator==(const CustomLayerRenderParameters& o) const {
    return projectionMatrix == o.projectionMatrix;
}

bool CustomLayerRenderParameters::operator!=(const CustomLayerRenderParameters& o) const {
    return !(*this == o);
}

} // namespace style
} // namespace mbgl
