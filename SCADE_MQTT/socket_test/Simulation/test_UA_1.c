/*********************************************************
 **
 ** File  test_UA_1.c
 **
 ** Automatically generated by SCADE Suite UA Adaptor
 ** Version R17 (build i15)
 ** 
 ** Date of generation: 2016-11-24T23:28:57
 ** Command line: C:/Program Files (x86)/Esterel Technologies/SCADE R17/SCADE/bin/uaadaptor.exe -sdy C:\Dev\ces-65\Tmp\socket_test\socket_test\socket_test.sdy -n C:\Program Files (x86)\Esterel Technologies\SCADE R17\SCADE Display\config\a661_description\a661.xml -outdir C:/Dev/ces-65/Tmp/socket_test/socket_test/Simulation -k C:/Dev/ces-65/Tmp/socket_test/socket_test/Simulation/kcg_trace.xml -o test_UA_1 -i socket_test_interface.h -encoding ASCII C:\Dev\ces-65\Tmp\socket_test\socket_test\DisplaySCADE(nova versao)\DisplayTS04.sgfx
 *********************************************************/
#include "kcg_sensors.h"
#include "test_UA_1.h"
#include "test_UA_1_constants.h"
#include "test_UA_1_private.h"

/********************************************************************************************
 * Send messages to the A661 server                                                         *
 ********************************************************************************************/
 uaa_size test_UA_1_send(buffer_el msg[], 
  outC_test* scade_ctx,  extern_out_ctx_t * extern_ctx){
  uaa_size offset = 0;
  
  offset = offset + a661_com_layer_1(msg + offset, scade_ctx, extern_ctx);
  return offset ;
}

/********************************************************************************************
 * Receive notifications from the A661 server                                               *
 ********************************************************************************************/
uaa_size test_UA_1_receive(buffer_el buffer[],  uaa_size buffer_size, 
  inC_test* scade_ctx,  extern_in_ctx_t * extern_ctx){
  uaa_size EvtString_byte_size = 0;
  uaa_size widget_event_structure_current_size = 0;
  uaa_size A661_Run_Time_Command_limit = 0;
  uaa_size root_current_size = 0;
  uaa_size n = 0;
  uaa_size next_n = 0;
  /*  type root */
  switch (buffer[ n ]){
    case A661_BEGIN_BLOCK : 
      root_current_size = READ_ULONG(( buffer + ( 4 + n ) ));
      next_n = ( n + root_current_size );
      /*  LayerIdent */
      switch (buffer[ ( 1 + n ) ]){
        case 1 : 
          /*  root */
          n = ( 8 + n );
          A661_Run_Time_Command_limit = ( ( n + root_current_size ) - 12 );
          while(( n < A661_Run_Time_Command_limit )){
            /*  type A661_Run_Time_Command */
            switch (READ_USHORT(( buffer + n ))){
              case A661_NOTIFY_WIDGET_EVENT : 
                widget_event_structure_current_size = READ_USHORT(( buffer + ( 2 + n ) ));
                next_n = ( n + widget_event_structure_current_size );
                /*  WidgetIdent */
                switch (READ_USHORT(( buffer + ( 4 + n ) ))){
                  case 47 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SEL_ENTRY_CHANGE : 
                        /*  SelectionListButton_A661_EVT_SEL_ENTRY_CHANGE */
                        /*  Notify */
                        scade_ctx->NotifyFromOcurrenceType = kcg_true;
                        /*  EvtEntryNumber */
                        scade_ctx->Title = READ_USHORT(( buffer + ( 4 + n ) ));
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 12 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SEL_ENTRY_CHANGE : 
                        /*  SelectionListButton_A661_EVT_SEL_ENTRY_CHANGE */
                        /*  EvtEntryNumber */
                        scade_ctx->Status = READ_USHORT(( buffer + ( 4 + n ) ));
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 7 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_STRING_CONFIRMED : 
                        EvtString_byte_size = READ_USHORT(( buffer + ( 4 + n ) ));
                        /*  EditBoxText_A661_EVT_STRING_CONFIRMED */
                        /*  Notify */
                        scade_ctx->Notification = kcg_true;
                        /*  EvtString */
                        LAYER("  ");
                        WIDGET("  ");
                        PARAMETER(" EvtString ");
                        CHECK_STRING_SIZE(" scade_ctx->Description ",
                          EvtString_byte_size, sizeof(scade_ctx->Description));
                        a661_assign_string(scade_ctx->Description,
                          ( buffer + ( 6 + n ) ), EvtString_byte_size);
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  case 5 : 
                    /*  widget_event_structure */
                    n = ( 6 + n );
                    /*  type EventStructure */
                    switch (READ_USHORT(( buffer + ( 2 + n ) ))){
                      case A661_EVT_SELECTION : 
                        /*  PushButton_A661_EVT_SELECTION */
                        /*  Notify */
                        scade_ctx->SignalFromButton = kcg_true;
                        break;
                      default : break;
                    }
                    n = next_n;
                    break;
                  default : break;
                }
                break;
              default : break;
            }
            n = next_n;
          }
          n = ( 4 + n );
          break;
        default : break;
      }
      break;
    default : break;
  }
  return n ;
}

/********************************************************************************************
 * Clear notifications                                                                      *
 ********************************************************************************************/
void test_UA_1_receive_clear(inC_test* scade_ctx, 
  extern_in_ctx_t * extern_ctx){
  scade_ctx->SignalFromButton = kcg_false;
  scade_ctx->Notification = kcg_false;
  scade_ctx->NotifyFromOcurrenceType = kcg_false;
}

/*********************************************************
 ** End of file
 ** End of generation: 2016-11-24T23:28:57
 *********************************************************/

