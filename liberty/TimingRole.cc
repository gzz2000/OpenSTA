// OpenSTA, Static Timing Analyzer
// Copyright (c) 2018, Parallax Software, Inc.
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "Machine.hh"
#include "TimingRole.hh"

namespace sta {

TimingRole *TimingRole::wire_;
TimingRole *TimingRole::combinational_;
TimingRole *TimingRole::tristate_enable_;
TimingRole *TimingRole::tristate_disable_;
TimingRole *TimingRole::reg_clk_q_;
TimingRole *TimingRole::reg_set_clr_;
TimingRole *TimingRole::latch_en_q_;
TimingRole *TimingRole::latch_d_q_;
TimingRole *TimingRole::sdf_iopath_;
TimingRole *TimingRole::setup_;
TimingRole *TimingRole::hold_;
TimingRole *TimingRole::recovery_;
TimingRole *TimingRole::removal_;
TimingRole *TimingRole::width_;
TimingRole *TimingRole::period_;
TimingRole *TimingRole::skew_;
TimingRole *TimingRole::nochange_;
TimingRole *TimingRole::output_setup_;
TimingRole *TimingRole::output_hold_;
TimingRole *TimingRole::gated_clk_setup_;
TimingRole *TimingRole::gated_clk_hold_;
TimingRole *TimingRole::latch_setup_;
TimingRole *TimingRole::latch_hold_;
TimingRole *TimingRole::data_check_setup_;
TimingRole *TimingRole::data_check_hold_;
TimingRole *TimingRole::non_seq_setup_;
TimingRole *TimingRole::non_seq_hold_;

TimingRoleMap TimingRole::timing_roles_;

void
TimingRole::init()
{
  wire_ = new TimingRole("wire", false, false, false, NULL, NULL, 0);
  combinational_ = new TimingRole("combinational", true, false,  false,
				  NULL, NULL, 1);
  tristate_enable_ = new TimingRole("tristate enable",
				    true, false, false,
				    NULL, NULL, 2);
  tristate_disable_ = new TimingRole("tristate disable",
				     true, false, false,
				     NULL, NULL, 3);
  reg_clk_q_ = new TimingRole("Reg Clk to Q", true, false, false,
			      NULL, NULL, 4);
  reg_set_clr_ = new TimingRole("Reg Set/Clr", true, false, false,
				NULL, NULL, 5);
  latch_en_q_ = new TimingRole("Latch En to Q", true, false, false,
			       NULL, TimingRole::regClkToQ(), 6);
  latch_d_q_ = new TimingRole("Latch D to Q", true, false, false,
			      NULL, NULL, 7);

  sdf_iopath_ = new TimingRole("sdf IOPATH", true, false, false,
			       NULL, NULL, 8);

  setup_ = new TimingRole("setup", false, true, false,
			  MinMax::max(), NULL, 9);
  hold_ = new TimingRole("hold", false, true, false,
			 MinMax::min(), NULL, 10);
  recovery_ = new TimingRole("recovery", false, true, false,
			     MinMax::max(), TimingRole::setup(), 11);
  removal_ = new TimingRole("removal", false, true, false,
			    MinMax::min(), TimingRole::hold(), 12);
  width_ = new TimingRole("width", false, true, false,
			  NULL, NULL, 13);
  period_ = new TimingRole("period", false, true, false,
			   NULL, NULL, 14);
  skew_ = new TimingRole("skew", false, true, false,
			 NULL, NULL, 15);
  nochange_ = new TimingRole("nochange", true, false, false,
			     NULL, NULL, 16);

  output_setup_ = new TimingRole("output setup", false, true, false,
				 MinMax::max(), TimingRole::setup(), 17);
  output_hold_ = new TimingRole("output hold", false, true, false,
				MinMax::min(), TimingRole::hold(), 18);
  gated_clk_setup_ = new TimingRole("clock gating setup",
				    false, true, false,
				    MinMax::max(), TimingRole::setup(),19);
  gated_clk_hold_ = new TimingRole("clock gating hold", false, true, false,
				   MinMax::min(), TimingRole::hold(),20);
  latch_setup_ = new TimingRole("latch setup", false, true, false,
				MinMax::max(), TimingRole::setup(),21);
  latch_hold_ = new TimingRole("latch hold", false, true, false,
			       MinMax::min(), TimingRole::hold(),22);
  data_check_setup_ = new TimingRole("data check setup",
				     false, true, false,
				     MinMax::max(),TimingRole::setup(),23);
  data_check_hold_ = new TimingRole("data check hold", false, true, false,
				    MinMax::min(), TimingRole::hold(), 24);
  non_seq_setup_ = new TimingRole("setup", false, true, true,
				  MinMax::max(), TimingRole::setup(), 25);
  non_seq_hold_ = new TimingRole("hold", false, true, true,
				 MinMax::min(), TimingRole::hold(), 26);
}

void
TimingRole::destroy()
{
  delete wire_;
  wire_ = NULL;
  delete combinational_;
  combinational_ = NULL;
  delete tristate_enable_;
  tristate_enable_ = NULL;
  delete tristate_disable_;
  tristate_disable_ = NULL;
  delete reg_clk_q_;
  reg_clk_q_ = NULL;
  delete reg_set_clr_;
  reg_set_clr_ = NULL;
  delete latch_en_q_;
  latch_en_q_ = NULL;
  delete latch_d_q_;
  latch_d_q_ = NULL;
  delete sdf_iopath_;
  sdf_iopath_ = NULL;
  delete setup_;
  setup_ = NULL;
  delete hold_;
  hold_ = NULL;
  delete recovery_;
  recovery_ = NULL;
  delete removal_;
  removal_ = NULL;
  delete width_;
  width_ = NULL;
  delete period_;
  period_ = NULL;
  delete skew_;
  skew_ = NULL;
  delete nochange_;
  nochange_ = NULL;
  delete output_setup_;
  output_setup_ = NULL;
  delete output_hold_;
  output_hold_ = NULL;
  delete gated_clk_setup_;
  gated_clk_setup_ = NULL;
  delete gated_clk_hold_;
  gated_clk_hold_ = NULL;
  delete latch_setup_;
  latch_setup_ = NULL;
  delete latch_hold_;
  latch_hold_ = NULL;
  delete data_check_setup_;
  data_check_setup_ = NULL;
  delete data_check_hold_;
  data_check_hold_ = NULL;
  delete non_seq_setup_;
  non_seq_setup_ = NULL;
  delete non_seq_hold_;
  non_seq_hold_ = NULL;
  timing_roles_.clear();
}

TimingRole::TimingRole(const char *name,
		       bool is_sdf_iopath,
		       bool is_timing_check,
		       bool is_non_seq_check,
		       MinMax *path_min_max,
		       TimingRole *generic_role,
		       int index) :
  name_(name),
  is_timing_check_(is_timing_check),
  is_sdf_iopath_(is_sdf_iopath),
  is_non_seq_check_(is_non_seq_check),
  generic_role_(generic_role),
  index_(index),
  path_min_max_(path_min_max)
{
  timing_roles_[name] = this;
}

TimingRole *
TimingRole::find(const char *name)
{
  return timing_roles_[name];
}

const TimingRole *
TimingRole::sdfRole() const
{
  if (is_sdf_iopath_)
    return sdf_iopath_;
  else
    return this;
}

const TimingRole *
TimingRole::genericRole() const
{
  if (generic_role_ == NULL)
    return this;
  else
    return generic_role_;
}

const EarlyLate *
TimingRole::tgtClkEarlyLate() const
{
  return path_min_max_->opposite();
}

bool
TimingRole::isWire() const
{
  return this == wire_;
}

bool
TimingRole::isAsyncTimingCheck() const
{
  return this == recovery_
    || this == removal_;
}

bool
TimingRole::isDataCheck() const
{
  return this == data_check_setup_
    || this == data_check_hold_;
}

bool
TimingRole::less(const TimingRole *role1,
		 const TimingRole *role2)
{
  return role1->index() < role2->index();
}

} // namespace