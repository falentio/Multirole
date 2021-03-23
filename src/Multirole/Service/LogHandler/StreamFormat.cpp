#include "StreamFormat.hpp"

#include <array>

namespace Ignis::Multirole::LogHandlerDetail
{

constexpr std::array<
	const char* const,
	static_cast<std::size_t>(ServiceType::SERVICE_TYPE_COUNT)
> SVC_NAMES =
{
	"GitRepository",
	"Multirole",
	"BanlistProvider",
	"CoreProvider",
	"DataProvider",
	"LogHandler",
	"ReplayManager",
	"ScriptProvider",
};

constexpr std::array<
	const char* const,
	static_cast<std::size_t>(ServiceType::SERVICE_TYPE_COUNT)
> LEVEL_NAMES =
{
	"Info",
	"Warning",
	"Error",
};

constexpr std::array<
	const char* const,
	static_cast<std::size_t>(ServiceType::SERVICE_TYPE_COUNT)
> EC_NAMES =
{
	"Core",
	"Official",
	"Speed",
	"Rush",
	"Unofficial",
};

template<typename T>
constexpr std::size_t AsSizeT(T v)
{
	return static_cast<std::size_t>(v);
}

void StreamFormat(std::ostream& os, const Timestamp& ts, const SinkLogProps& props, std::string_view str) noexcept
{
	FmtTimestamp(os, ts);
	if(std::holds_alternative<SvcLogProps>(props))
	{
		const auto& svcLogProps = std::get<0>(props);
		os << " [Service:" << SVC_NAMES[AsSizeT(svcLogProps.first)] << ']'
		   << " [Level:" << LEVEL_NAMES[AsSizeT(svcLogProps.second)] << ']';
	}
	else // std::holds_alternative<ECLogProps>(props)
	{
		const auto& ecLogProps = std::get<1>(props);
		os << " [EC:" << EC_NAMES[AsSizeT(ecLogProps.first)] << ']'
		   << " [ReplayID:" << ecLogProps.second << ']';
	}
	os << ' ' << str << '\n';
}

} // namespace Ignis::Multirole::LogHandlerDetail
