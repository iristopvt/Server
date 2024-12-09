// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Protocol.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3020000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3020002 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_Protocol_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_Protocol_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Protocol_2eproto;
namespace Protocol {
class BuffData;
struct BuffDataDefaultTypeInternal;
extern BuffDataDefaultTypeInternal _BuffData_default_instance_;
class PlayerInfo;
struct PlayerInfoDefaultTypeInternal;
extern PlayerInfoDefaultTypeInternal _PlayerInfo_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::BuffData* Arena::CreateMaybeMessage<::Protocol::BuffData>(Arena*);
template<> ::Protocol::PlayerInfo* Arena::CreateMaybeMessage<::Protocol::PlayerInfo>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class BuffData final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.BuffData) */ {
 public:
  inline BuffData() : BuffData(nullptr) {}
  ~BuffData() override;
  explicit PROTOBUF_CONSTEXPR BuffData(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  BuffData(const BuffData& from);
  BuffData(BuffData&& from) noexcept
    : BuffData() {
    *this = ::std::move(from);
  }

  inline BuffData& operator=(const BuffData& from) {
    CopyFrom(from);
    return *this;
  }
  inline BuffData& operator=(BuffData&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const BuffData& default_instance() {
    return *internal_default_instance();
  }
  static inline const BuffData* internal_default_instance() {
    return reinterpret_cast<const BuffData*>(
               &_BuffData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(BuffData& a, BuffData& b) {
    a.Swap(&b);
  }
  inline void Swap(BuffData* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(BuffData* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  BuffData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<BuffData>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const BuffData& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const BuffData& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(BuffData* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.BuffData";
  }
  protected:
  explicit BuffData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kVictimsFieldNumber = 3,
    kBuffIdFieldNumber = 1,
    kRemainTimeFieldNumber = 2,
  };
  // repeated uint32 victims = 3;
  int victims_size() const;
  private:
  int _internal_victims_size() const;
  public:
  void clear_victims();
  private:
  uint32_t _internal_victims(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      _internal_victims() const;
  void _internal_add_victims(uint32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      _internal_mutable_victims();
  public:
  uint32_t victims(int index) const;
  void set_victims(int index, uint32_t value);
  void add_victims(uint32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
      victims() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
      mutable_victims();

  // uint32 buffId = 1;
  void clear_buffid();
  uint32_t buffid() const;
  void set_buffid(uint32_t value);
  private:
  uint32_t _internal_buffid() const;
  void _internal_set_buffid(uint32_t value);
  public:

  // float remainTime = 2;
  void clear_remaintime();
  float remaintime() const;
  void set_remaintime(float value);
  private:
  float _internal_remaintime() const;
  void _internal_set_remaintime(float value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.BuffData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t > victims_;
  mutable std::atomic<int> _victims_cached_byte_size_;
  uint32_t buffid_;
  float remaintime_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class PlayerInfo final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.PlayerInfo) */ {
 public:
  inline PlayerInfo() : PlayerInfo(nullptr) {}
  ~PlayerInfo() override;
  explicit PROTOBUF_CONSTEXPR PlayerInfo(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  PlayerInfo(const PlayerInfo& from);
  PlayerInfo(PlayerInfo&& from) noexcept
    : PlayerInfo() {
    *this = ::std::move(from);
  }

  inline PlayerInfo& operator=(const PlayerInfo& from) {
    CopyFrom(from);
    return *this;
  }
  inline PlayerInfo& operator=(PlayerInfo&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const PlayerInfo& default_instance() {
    return *internal_default_instance();
  }
  static inline const PlayerInfo* internal_default_instance() {
    return reinterpret_cast<const PlayerInfo*>(
               &_PlayerInfo_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(PlayerInfo& a, PlayerInfo& b) {
    a.Swap(&b);
  }
  inline void Swap(PlayerInfo* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(PlayerInfo* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  PlayerInfo* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<PlayerInfo>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const PlayerInfo& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const PlayerInfo& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(PlayerInfo* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.PlayerInfo";
  }
  protected:
  explicit PlayerInfo(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kBuffsFieldNumber = 4,
    kIdFieldNumber = 1,
    kHpFieldNumber = 2,
    kAtkFieldNumber = 3,
  };
  // repeated .Protocol.BuffData buffs = 4;
  int buffs_size() const;
  private:
  int _internal_buffs_size() const;
  public:
  void clear_buffs();
  ::Protocol::BuffData* mutable_buffs(int index);
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
      mutable_buffs();
  private:
  const ::Protocol::BuffData& _internal_buffs(int index) const;
  ::Protocol::BuffData* _internal_add_buffs();
  public:
  const ::Protocol::BuffData& buffs(int index) const;
  ::Protocol::BuffData* add_buffs();
  const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
      buffs() const;

  // uint64 id = 1;
  void clear_id();
  uint64_t id() const;
  void set_id(uint64_t value);
  private:
  uint64_t _internal_id() const;
  void _internal_set_id(uint64_t value);
  public:

  // uint32 hp = 2;
  void clear_hp();
  uint32_t hp() const;
  void set_hp(uint32_t value);
  private:
  uint32_t _internal_hp() const;
  void _internal_set_hp(uint32_t value);
  public:

  // uint32 atk = 3;
  void clear_atk();
  uint32_t atk() const;
  void set_atk(uint32_t value);
  private:
  uint32_t _internal_atk() const;
  void _internal_set_atk(uint32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.PlayerInfo)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData > buffs_;
  uint64_t id_;
  uint32_t hp_;
  uint32_t atk_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_Protocol_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// BuffData

// uint32 buffId = 1;
inline void BuffData::clear_buffid() {
  buffid_ = 0u;
}
inline uint32_t BuffData::_internal_buffid() const {
  return buffid_;
}
inline uint32_t BuffData::buffid() const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.buffId)
  return _internal_buffid();
}
inline void BuffData::_internal_set_buffid(uint32_t value) {
  
  buffid_ = value;
}
inline void BuffData::set_buffid(uint32_t value) {
  _internal_set_buffid(value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.buffId)
}

// float remainTime = 2;
inline void BuffData::clear_remaintime() {
  remaintime_ = 0;
}
inline float BuffData::_internal_remaintime() const {
  return remaintime_;
}
inline float BuffData::remaintime() const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.remainTime)
  return _internal_remaintime();
}
inline void BuffData::_internal_set_remaintime(float value) {
  
  remaintime_ = value;
}
inline void BuffData::set_remaintime(float value) {
  _internal_set_remaintime(value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.remainTime)
}

// repeated uint32 victims = 3;
inline int BuffData::_internal_victims_size() const {
  return victims_.size();
}
inline int BuffData::victims_size() const {
  return _internal_victims_size();
}
inline void BuffData::clear_victims() {
  victims_.Clear();
}
inline uint32_t BuffData::_internal_victims(int index) const {
  return victims_.Get(index);
}
inline uint32_t BuffData::victims(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.victims)
  return _internal_victims(index);
}
inline void BuffData::set_victims(int index, uint32_t value) {
  victims_.Set(index, value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.victims)
}
inline void BuffData::_internal_add_victims(uint32_t value) {
  victims_.Add(value);
}
inline void BuffData::add_victims(uint32_t value) {
  _internal_add_victims(value);
  // @@protoc_insertion_point(field_add:Protocol.BuffData.victims)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
BuffData::_internal_victims() const {
  return victims_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >&
BuffData::victims() const {
  // @@protoc_insertion_point(field_list:Protocol.BuffData.victims)
  return _internal_victims();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
BuffData::_internal_mutable_victims() {
  return &victims_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< uint32_t >*
BuffData::mutable_victims() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.BuffData.victims)
  return _internal_mutable_victims();
}

// -------------------------------------------------------------------

// PlayerInfo

// uint64 id = 1;
inline void PlayerInfo::clear_id() {
  id_ = uint64_t{0u};
}
inline uint64_t PlayerInfo::_internal_id() const {
  return id_;
}
inline uint64_t PlayerInfo::id() const {
  // @@protoc_insertion_point(field_get:Protocol.PlayerInfo.id)
  return _internal_id();
}
inline void PlayerInfo::_internal_set_id(uint64_t value) {
  
  id_ = value;
}
inline void PlayerInfo::set_id(uint64_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Protocol.PlayerInfo.id)
}

// uint32 hp = 2;
inline void PlayerInfo::clear_hp() {
  hp_ = 0u;
}
inline uint32_t PlayerInfo::_internal_hp() const {
  return hp_;
}
inline uint32_t PlayerInfo::hp() const {
  // @@protoc_insertion_point(field_get:Protocol.PlayerInfo.hp)
  return _internal_hp();
}
inline void PlayerInfo::_internal_set_hp(uint32_t value) {
  
  hp_ = value;
}
inline void PlayerInfo::set_hp(uint32_t value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:Protocol.PlayerInfo.hp)
}

// uint32 atk = 3;
inline void PlayerInfo::clear_atk() {
  atk_ = 0u;
}
inline uint32_t PlayerInfo::_internal_atk() const {
  return atk_;
}
inline uint32_t PlayerInfo::atk() const {
  // @@protoc_insertion_point(field_get:Protocol.PlayerInfo.atk)
  return _internal_atk();
}
inline void PlayerInfo::_internal_set_atk(uint32_t value) {
  
  atk_ = value;
}
inline void PlayerInfo::set_atk(uint32_t value) {
  _internal_set_atk(value);
  // @@protoc_insertion_point(field_set:Protocol.PlayerInfo.atk)
}

// repeated .Protocol.BuffData buffs = 4;
inline int PlayerInfo::_internal_buffs_size() const {
  return buffs_.size();
}
inline int PlayerInfo::buffs_size() const {
  return _internal_buffs_size();
}
inline void PlayerInfo::clear_buffs() {
  buffs_.Clear();
}
inline ::Protocol::BuffData* PlayerInfo::mutable_buffs(int index) {
  // @@protoc_insertion_point(field_mutable:Protocol.PlayerInfo.buffs)
  return buffs_.Mutable(index);
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >*
PlayerInfo::mutable_buffs() {
  // @@protoc_insertion_point(field_mutable_list:Protocol.PlayerInfo.buffs)
  return &buffs_;
}
inline const ::Protocol::BuffData& PlayerInfo::_internal_buffs(int index) const {
  return buffs_.Get(index);
}
inline const ::Protocol::BuffData& PlayerInfo::buffs(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.PlayerInfo.buffs)
  return _internal_buffs(index);
}
inline ::Protocol::BuffData* PlayerInfo::_internal_add_buffs() {
  return buffs_.Add();
}
inline ::Protocol::BuffData* PlayerInfo::add_buffs() {
  ::Protocol::BuffData* _add = _internal_add_buffs();
  // @@protoc_insertion_point(field_add:Protocol.PlayerInfo.buffs)
  return _add;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedPtrField< ::Protocol::BuffData >&
PlayerInfo::buffs() const {
  // @@protoc_insertion_point(field_list:Protocol.PlayerInfo.buffs)
  return buffs_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_Protocol_2eproto
