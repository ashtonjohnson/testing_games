/*
  Created by Surgeworks, Inc. http://surgeworksmobile.com/
  
  This work is licensed under a Creative Commons Attribution 3.0 Unported License.
  http://creativecommons.org/licenses/by/3.0/

*/


@interface AlertDialog : NSObject
{
	BOOL isAlertActive;
    UIAlertView *alertTextBoxView;
}

+ (AlertDialog*) instance;
- (void) showNotEnoughCoinsDialogue:(NSString*)title messageAlert:(NSString*)message  button0:(NSString*)button0 button1:(NSString*)button1 button2:(NSString*)button2 calling:(NSString*)calling;
-(void)showDialogueFromMainMenuChar:(NSString*)prms;
-(void) showDialogWithTextBox:(NSString*) title messageAlert:(NSString*)message button0:(NSString*)button0 calling:(NSString *)calling;

@end

/*

DISCLAIMER OF WARRANTY.

SURGEWORKS expressly disclaims any warranty for the SOFTWARE COMPONENT PRODUCT(S). THE SOFTWARE COMPONENT PRODUCT(S) AND ANY RELATED DOCUMENTATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, OR NONINFRINGEMENT. SURGEWORKS DOES NOT WARRANT, GUARANTEE, OR MAKE ANY REPRESENTATIONS REGARDING THE USE, OR THE RESULTS OF THE USE, OF THE SOFTWARE COMPONENT PRODUCT(S) IN TERMS OF CORRECTNESS, ACCURACY, RELIABILITY, OR OTHERWISE. THE ENTIRE RISK ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE COMPONENT PRODUCT(S) REMAINS WITH YOU. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. No oral or written information or advice given by SURGEWORKS or its employees shall create a warranty or in any way increase the scope of this warranty.

LIMITATIONS ON LIABILITY.

To the maximum extent permitted by applicable law, in no event shall SURGEWORKS be liable for any special, incidental, indirect, or consequential damages whatsoever (including, without limitation, damages for loss of business profits, business interruption, loss of business information, or any other pecuniary loss) arising out of the use of or inability to use the SOFTWARE COMPONENT PRODUCT(S) or the provision of or failure to provide Support Services, even if SURGEWORKS has been advised of the possibility of such damages.

Developer End User understands that the SOFTWARE COMPONENT PRODUCT(S) may produce inaccurate results because of a failure or fault within the SOFTWARE COMPONENT PRODUCT(S) or failure by Developer End User to properly use and or deploy the SOFTWARE COMPONENT PRODUCT(S). Developer End User assumes full and sole responsibility for any use of the SOFTWARE COMPONENT PRODUCT(S), and bears the entire risk for failures or faults within the SOFTWARE COMPONENT PRODUCT(S). You agree that regardless of the cause of failure or fault or the form of any claim, YOUR SOLE REMEDY AND SURGEWORKS'S SOLE OBLIGATION SHALL BE GOVERNED BY THIS AGREEMENT AND IN NO EVENT SHALL SURGEWORKS'S LIABILITY EXCEED THE PRICE PAID TO SURGEWORKS FOR THE SOFTWARE COMPONENT PRODUCT(S). This Limited Warranty is void if failure of the SOFTWARE COMPONENT PRODUCT(S) has resulted from accident, abuse, alteration, unauthorized use or misapplication of the SOFTWARE COMPONENT PRODUCT(S).

*/