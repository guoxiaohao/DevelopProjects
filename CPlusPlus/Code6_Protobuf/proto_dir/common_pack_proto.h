#pragma once

#include "server2client.pb.h"

template<typename Proto>
std::string MsgContent_proto(Proto &pro)
{
	std::string str_data;
	pro.SerializeToString(&str_data);

	server2client::msg_content data_content;
	data_content.set_type((int)Proto::id);
	data_content.set_datas(str_data);

	std::string msg;
	data_content.SerializeToString(&msg);
	return msg;
}