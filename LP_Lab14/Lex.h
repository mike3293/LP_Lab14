#pragma once

#include "IT.h"
#include "LT.h"
#include "Log.h"
#include "In.h"

namespace Lex
{
	struct LEX
	{
		IT::IdTable idtable;
		LT::LexTable lextable;
	};

	LEX lexAnaliz(Log::LOG log, In::IN in);
}