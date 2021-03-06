
#include "hazard.h"

/**
 * Callback for the hazrd detection of \c hazard module.
 */
void hazard::detect_hazard()
{
    // control hazards
    if (BranchTaken.read() != 0) {
        enable_pc.write(true);
        enable_ifid.write(true);
        reset_ifid.write(true);
        reset_idexe.write(false);
    }
    // data hazards
    else if( rs.read() != 0 && rs.read() == WriteReg_exe.read() && RegWrite_exe.read() == true
        || rs.read() != 0 && rs.read() == WriteReg_mem1.read() && RegWrite_mem1.read() == true
        || rs.read() != 0 && rs.read() == WriteReg_mem2.read() && RegWrite_mem2.read() == true
        || rt.read() != 0 && rt.read() == WriteReg_exe.read() && RegWrite_exe.read() == true
        || rt.read() != 0 && rt.read() == WriteReg_mem1.read() && RegWrite_mem1.read() == true
        || rt.read() != 0 && rt.read() == WriteReg_mem2.read() && RegWrite_mem2.read() == true) {

        enable_pc.write(false);
        enable_ifid.write(false);
        reset_ifid.write(false);
        reset_idexe.write(true);
    }
    else {
        enable_pc.write(true);
        enable_ifid.write(true);
        reset_ifid.write(false);
        reset_idexe.write(false);
    }
}
