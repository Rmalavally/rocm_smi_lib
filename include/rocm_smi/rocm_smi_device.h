/*
 * =============================================================================
 *   ROC Runtime Conformance Release License
 * =============================================================================
 * The University of Illinois/NCSA
 * Open Source License (NCSA)
 *
 * Copyright (c) 2017, Advanced Micro Devices, Inc.
 * All rights reserved.
 *
 * Developed by:
 *
 *                 AMD Research and AMD ROC Software Development
 *
 *                 Advanced Micro Devices, Inc.
 *
 *                 www.amd.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal with the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 *  - Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimers.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimers in
 *    the documentation and/or other materials provided with the distribution.
 *  - Neither the names of <Name of Development Group, Name of Institution>,
 *    nor the names of its contributors may be used to endorse or promote
 *    products derived from this Software without specific prior written
 *    permission.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS WITH THE SOFTWARE.
 *
 */
#ifndef ROCM_SMI_LIB_INCLUDE_ROCM_SMI_ROCM_SMI_DEVICE_H_
#define ROCM_SMI_LIB_INCLUDE_ROCM_SMI_ROCM_SMI_DEVICE_H_
#include <string>
#include <memory>
#include <utility>
#include <cstdint>
#include <vector>

#include "rocm_smi/rocm_smi_monitor.h"
#include "rocm_smi/rocm_smi_power_mon.h"

namespace amd {
namespace smi {

enum DevInfoTypes {
  kDevPerfLevel,
  kDevOverDriveLevel,
  kDevDevID,
  kDevGPUMClk,
  kDevGPUSClk,
  kDevPowerProfileMode
};

class Device {
 public:
    explicit Device(std::string path);
    ~Device(void);

    void set_monitor(std::shared_ptr<Monitor> m) {monitor_ = m;}
    std::string path(void) const {return path_;}
    const std::shared_ptr<Monitor>& monitor() {return monitor_;}
    const std::shared_ptr<PowerMon>& power_monitor() {return power_monitor_;}
    void set_power_monitor(std::shared_ptr<PowerMon> pm) {power_monitor_ = pm;}

    int readDevInfo(DevInfoTypes type, uint32_t *val);
    int readDevInfo(DevInfoTypes type, std::string *val);
    int readDevInfo(DevInfoTypes type, std::vector<std::string> *retVec);
    int writeDevInfo(DevInfoTypes type, uint64_t val);
    int writeDevInfo(DevInfoTypes type, std::string val);
    uint32_t index(void) const {return index_;}
    void set_index(uint32_t index) {index_ = index;}

 private:
    std::shared_ptr<Monitor> monitor_;
    std::shared_ptr<PowerMon> power_monitor_;
    std::string path_;
    uint32_t index_;
    int readDevInfoStr(DevInfoTypes type, std::string *retStr);
    int readDevInfoMultiLineStr(DevInfoTypes type,
                                            std::vector<std::string> *retVec);
    int writeDevInfoStr(DevInfoTypes type, std::string valStr);
};

}  // namespace smi
}  // namespace amd

#endif  // ROCM_SMI_LIB_INCLUDE_ROCM_SMI_ROCM_SMI_DEVICE_H_