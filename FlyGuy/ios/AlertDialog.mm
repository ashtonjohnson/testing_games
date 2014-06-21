
/*
 Created by Surgeworks, Inc. http://surgeworksmobile.com/
 
 How to use :
 
 [[AlertDialog instance] showAlertDialog];
 
 Just add this line of code to your code implementation,
 for example in applicationDidFinishLaunching: method and 
 #import "ReviewsAlert.h" in same file.
 
 Set kDaysToWait to define time interval.
 Set AppUrl to yours app AppSore url.
 
*/


#import "AlertDialog.h"
#import "Utility.h"
#import "IOSNDKHelper.h"

NSString *callingScreen = @"";
static AlertDialog *instance   = nil;

@implementation AlertDialog

- (void) showNotEnoughCoinsDialogue:(NSString*)title messageAlert:(NSString*)message  button0:(NSString*)button0 button1:(NSString*)button1 button2:(NSString*)button2 calling:(NSString *)calling
{
	if (isAlertActive == NO)
	{
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle: title
															message: message
														   delegate: self
												  cancelButtonTitle: button2
												  otherButtonTitles: button0, button1, nil];
		[alertView show];
		isAlertActive = YES;
        callingScreen = [[NSString alloc]initWithString:calling];
	}
}

-(void) showDialogWithTextBox:(NSString*) title messageAlert:(NSString*)message button0:(NSString*)button0 calling:(NSString *)calling {
	if (isAlertActive == NO)
	{
		alertTextBoxView = [[UIAlertView alloc] initWithTitle: title
															message: message
														   delegate: self
												  cancelButtonTitle: button0
												  otherButtonTitles: nil];
        alertTextBoxView.alertViewStyle = UIAlertViewStylePlainTextInput;
      callingScreen = [[NSString alloc]initWithString:calling];
        [alertTextBoxView show];
		isAlertActive = YES;
	}
}

- (void) alertView:(UIAlertView *)theAlertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex == 0) 
	{
        CCLOG("cancel button");
        if ([callingScreen isEqualToString:@"mainScreen"]) {
            NSLog(@"callFromMainScreen");
        } else if ([callingScreen isEqualToString:@"upgradeScreen"]) {
            NSLog(@"callFromUpgradeScreen");
        }else if ([callingScreen isEqualToString:@"scoreScreen"]){
            NSLog(@"cancel");
        }else if ([callingScreen isEqualToString:@"yesToConfirm"]){
            NSLog(@"yes to confirm");
            UITextField *textField = [alertTextBoxView textFieldAtIndex:0];
            if ([textField.text caseInsensitiveCompare:@"yes"]) {
                CCLOG("no");
                
                 [self showNotEnoughCoinsDialogue:@"You must type Yes, Reset cancelled" messageAlert:@"" button0:@"Ok" button1:NULL button2:NULL calling:@"scoreScreen"];
            } else {
                CCLOG("yes");
            NSDictionary *dict = @{@"hiiii": @"hello"};
            [IOSNDKHelper SendMessage:@"replaceWithMainMenuScreen" WithParameters:dict];
            }
        }
	}
	else if (buttonIndex == 1) 
	{ 
        CCLOG("visit button");
        if ([callingScreen isEqualToString: @"mainScreen"]) {
            NSLog(@"callFromMainScreen");
            NSDictionary *dict = @{@"hiiii": @"hello"};
            [IOSNDKHelper SendMessage:@"goToUpgradeScreenWithExtras" WithParameters:dict];
        } else if ([callingScreen isEqualToString:@"upgradeScreen"]){
            NSLog(@"callFromUpgradeScreen");
            NSDictionary *dict = @{@"hiiii": @"hello"};
            [IOSNDKHelper SendMessage:@"goToUpgradeScreenWithCoinsStars" WithParameters:dict];
        }else if ([callingScreen isEqualToString:@"scoreScreen"]){
            NSLog(@"yes, reset it");
            isAlertActive = NO;
            [self showDialogWithTextBox:@"Type Yes to confirm reset:" messageAlert:@"" button0:@"Ok" calling:@"yesToConfirm"];
        }
    }
    else if (buttonIndex == 2)
	{
            CCLOG("unlock button");
        if ([callingScreen isEqualToString: @"mainScreen"]) {
            NSLog(@"callFromMainScreen");
            CCLOG("unlock all chars");
            NSDictionary *dict = @{@"hiiii": @"hello"};
            [IOSNDKHelper SendMessage:@"unlockAllChars" WithParameters:dict];
        } else if ([callingScreen isEqualToString:@"upgradeScreen"]){
            NSLog(@"callFromUpgradeScreen");
        } else if ([callingScreen isEqualToString:@"scoreScreen"]){
//            NSLog(@"yes reset it");
        }
	}
	[theAlertView release];
	isAlertActive = NO;
    [callingScreen release];
}

+ (AlertDialog*) instance
{
    @synchronized(self) 
    {
        if (instance == nil) 
        {
            [[self alloc] init];
        }
    }
    return instance;
}

+ (id)allocWithZone:(NSZone*) zone
{
    @synchronized(self) 
    {
        if (instance == nil) 
        {
            instance = [super allocWithZone:zone];
            return instance;
        }
    }
    return nil; 
}

- (id) copyWithZone:(NSZone *)zone
{
    return self;
}

- (id) retain
{
    return self;
}

- (unsigned) retainCount
{
    return UINT_MAX;
}

- (void) release
{
	
}

- (id) autorelease
{
    return self;
}

@end

/*

DISCLAIMER OF WARRANTY.

SURGEWORKS expressly disclaims any warranty for the SOFTWARE COMPONENT PRODUCT(S). THE SOFTWARE COMPONENT PRODUCT(S) AND ANY RELATED DOCUMENTATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT. SURGEWORKS DOES NOT WARRANT, GUARANTEE, OR MAKE ANY REPRESENTATIONS REGARDING THE USE, OR THE RESULTS OF THE USE, OF THE SOFTWARE COMPONENT PRODUCT(S) IN TERMS OF CORRECTNESS, ACCURACY, RELIABILITY, OR OTHERWISE. THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE COMPONENT PRODUCT(S) REMAINS WITH YOU. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. No oral or written information or advice given by SURGEWORKS or its employees shall create a warranty or in any way increase the scope of this warranty.

LIMITATIONS ON LIABILITY.

To the maximum extent permitted by applicable law, in no event shall SURGEWORKS be liable for any special, incidental, indirect, or consequential damages whatsoever (including, without limitation, damages for loss of business profits, business interruption, loss of business information, or any other pecuniary loss) arising out of the use of or inability to use the SOFTWARE COMPONENT PRODUCT(S) or the provision of or failure to provide Support Services, even if SURGEWORKS has been advised of the possibility of such damages.

Developer End User understands that the SOFTWARE COMPONENT PRODUCT(S) may produce inaccurate results because of a failure or fault within the SOFTWARE COMPONENT PRODUCT(S) or failure by Developer End User to properly use and or deploy the SOFTWARE COMPONENT PRODUCT(S). Developer End User assumes full and sole responsibility for any use of the SOFTWARE COMPONENT PRODUCT(S), and bears the entire risk for failures or faults within the SOFTWARE COMPONENT PRODUCT(S). You agree that regardless of the cause of failure or fault or the form of any claim, YOUR SOLE REMEDY AND SURGEWORKS'S SOLE OBLIGATION SHALL BE GOVERNED BY THIS AGREEMENT AND IN NO EVENT SHALL SURGEWORKS'S LIABILITY EXCEED THE PRICE PAID TO SURGEWORKS FOR THE SOFTWARE COMPONENT PRODUCT(S). This Limited Warranty is void if failure of the SOFTWARE COMPONENT PRODUCT(S) has resulted from accident, abuse, alteration, unauthorized use or misapplication of the SOFTWARE COMPONENT PRODUCT(S).

*/