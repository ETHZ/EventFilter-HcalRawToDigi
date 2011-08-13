#include <cassert>
#include "DataFormats/HcalDigi/interface/HcalUpgradeDataFrame.h"
#include "EventFilter/HcalRawToDigi/interface/HcalUpgradePackingScheme.h"

bool testUpgradeFrame(const HcalDetId & detId, int nadc, int ntdc) 
{
  HcalUpgradeDataFrame digi(detId, 0, 10, 2);
  unsigned short i = 0;
  for(; i < 10; ++i) {
    // just set it to the sample #
    digi.setSample(i,i,i,true);
  }
  unsigned char packed[11] = {0};
  HcalUpgradePackingScheme packingScheme;
  packingScheme.pack(digi, packed);
  HcalUpgradeDataFrame digi2(detId);
  packingScheme.unpack(packed, digi2);
std::cout << digi << " " << digi2 << std::endl;
  int n = std::max(nadc, ntdc);
  for(i=0; i < n; ++i) {
    if(i < nadc) {
      assert(digi.adc(i) == digi2.adc(i));
    }
    if(i < ntdc) {
      assert(digi.tdc(i) == digi2.tdc(i));
    }
  }
  return true;
}

int main() {
  bool result = true;
  result = testUpgradeFrame(HcalDetId(HcalBarrel, 1,1,1), 8, 4);
  result = testUpgradeFrame(HcalDetId(HcalEndcap, 21,1,1), 6, 6);
  result = testUpgradeFrame(HcalDetId(HcalOuter, 1,1,1), 8, 4);
  result = testUpgradeFrame(HcalDetId(HcalForward, 1,1,1), 4, 4);
  return result;
  }
