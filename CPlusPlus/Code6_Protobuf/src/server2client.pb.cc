// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: server2client.proto

#include "server2client.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

class server2clientDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<server2client> _instance;
} _server2client_default_instance_;
static void InitDefaultsserver2client_server2client_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_server2client_default_instance_;
    new (ptr) ::server2client();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::server2client::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_server2client_server2client_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsserver2client_server2client_2eproto}, {}};

void InitDefaults_server2client_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_server2client_server2client_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_server2client_2eproto[1];
constexpr ::google::protobuf::EnumDescriptor const** file_level_enum_descriptors_server2client_2eproto = nullptr;
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_server2client_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_server2client_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::server2client, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::server2client, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::server2client, type_),
  PROTOBUF_FIELD_OFFSET(::server2client, command_type_),
  1,
  0,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::server2client)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::_server2client_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_server2client_2eproto = {
  {}, AddDescriptors_server2client_2eproto, "server2client.proto", schemas,
  file_default_instances, TableStruct_server2client_2eproto::offsets,
  file_level_metadata_server2client_2eproto, 1, file_level_enum_descriptors_server2client_2eproto, file_level_service_descriptors_server2client_2eproto,
};

const char descriptor_table_protodef_server2client_2eproto[] =
  "\n\023server2client.proto\"3\n\rserver2client\022\014"
  "\n\004type\030\001 \002(\005\022\024\n\014command_type\030\002 \002(\t"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_server2client_2eproto = {
  false, InitDefaults_server2client_2eproto, 
  descriptor_table_protodef_server2client_2eproto,
  "server2client.proto", &assign_descriptors_table_server2client_2eproto, 74,
};

void AddDescriptors_server2client_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_server2client_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_server2client_2eproto = []() { AddDescriptors_server2client_2eproto(); return true; }();

// ===================================================================

void server2client::InitAsDefaultInstance() {
}
class server2client::HasBitSetters {
 public:
  static void set_has_type(server2client* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
  static void set_has_command_type(server2client* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int server2client::kTypeFieldNumber;
const int server2client::kCommandTypeFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

server2client::server2client()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:server2client)
}
server2client::server2client(const server2client& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  command_type_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_command_type()) {
    command_type_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.command_type_);
  }
  type_ = from.type_;
  // @@protoc_insertion_point(copy_constructor:server2client)
}

void server2client::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_server2client_server2client_2eproto.base);
  command_type_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  type_ = 0;
}

server2client::~server2client() {
  // @@protoc_insertion_point(destructor:server2client)
  SharedDtor();
}

void server2client::SharedDtor() {
  command_type_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void server2client::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const server2client& server2client::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_server2client_server2client_2eproto.base);
  return *internal_default_instance();
}


void server2client::Clear() {
// @@protoc_insertion_point(message_clear_start:server2client)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    command_type_.ClearNonDefaultToEmptyNoArena();
  }
  type_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* server2client::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<server2client*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // required int32 type = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        msg->set_type(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required string command_type = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 18) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        ctx->extra_parse_data().SetFieldName("server2client.command_type");
        object = msg->mutable_command_type();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8Verify;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8Verify(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool server2client::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:server2client)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 type = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          HasBitSetters::set_has_type(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required string command_type = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (18 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_command_type()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->command_type().data(), static_cast<int>(this->command_type().length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "server2client.command_type");
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:server2client)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:server2client)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void server2client::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:server2client)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 type = 1;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->type(), output);
  }

  // required string command_type = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->command_type().data(), static_cast<int>(this->command_type().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "server2client.command_type");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->command_type(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:server2client)
}

::google::protobuf::uint8* server2client::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:server2client)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 type = 1;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->type(), target);
  }

  // required string command_type = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->command_type().data(), static_cast<int>(this->command_type().length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "server2client.command_type");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->command_type(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:server2client)
  return target;
}

size_t server2client::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:server2client)
  size_t total_size = 0;

  if (has_command_type()) {
    // required string command_type = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->command_type());
  }

  if (has_type()) {
    // required int32 type = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->type());
  }

  return total_size;
}
size_t server2client::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:server2client)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required string command_type = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->command_type());

    // required int32 type = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->type());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void server2client::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:server2client)
  GOOGLE_DCHECK_NE(&from, this);
  const server2client* source =
      ::google::protobuf::DynamicCastToGenerated<server2client>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:server2client)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:server2client)
    MergeFrom(*source);
  }
}

void server2client::MergeFrom(const server2client& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:server2client)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      command_type_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.command_type_);
    }
    if (cached_has_bits & 0x00000002u) {
      type_ = from.type_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void server2client::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:server2client)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void server2client::CopyFrom(const server2client& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:server2client)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool server2client::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void server2client::Swap(server2client* other) {
  if (other == this) return;
  InternalSwap(other);
}
void server2client::InternalSwap(server2client* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  command_type_.Swap(&other->command_type_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(type_, other->type_);
}

::google::protobuf::Metadata server2client::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_server2client_2eproto);
  return ::file_level_metadata_server2client_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::server2client* Arena::CreateMaybeMessage< ::server2client >(Arena* arena) {
  return Arena::CreateInternal< ::server2client >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
